// SPDX-License-Identifier: GPL-2.0-only

#include <arpa/inet.h>
#include <dirent.h>
#include <fcntl.h>
#include <linux/sockios.h>
#include <linux/wireless.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/random.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <cctype>
#include <cerrno>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

namespace {

constexpr const char *kModule = "88x2eu_ohd";
constexpr const char *kDefaultMap = "/etc/wifi/wifi_efuse_88x2eu_ohd.map";
constexpr const char *kDefaultMask = "/etc/wifi/wifi_efuse_88x2eu_ohd.mask";
constexpr const char *kDefaultRegistry = "/var/lib/openhd-efuse/mac-addresses";
constexpr std::size_t kIoctlBufferSize = 2047;
constexpr unsigned kMacOffset = 0x157;
constexpr std::array<unsigned char, 3> kRealtekOui{{0x00, 0xE0, 0x4C}};

using Mac = std::array<unsigned char, 6>;
using CommandHook = std::function<std::string(const std::string &, const std::string &)>;
CommandHook command_hook;
volatile std::sig_atomic_t stop_requested = 0;

struct Options {
    std::string interface = "wlan1";
    std::string map_path = kDefaultMap;
    std::string mask_path = kDefaultMask;
    std::string registry_path = kDefaultRegistry;
    std::optional<Mac> requested_mac;
    bool assume_yes = false;
    bool no_reload = false;
    bool self_test = false;
    bool rf_test = false;
    unsigned bandwidth_mhz = 0;
    unsigned duration_seconds = 10;
    bool duration_set = false;
};

struct CommandResult {
    int status = -1;
    std::string output;
};

[[noreturn]] void fail(const std::string &message) {
    throw std::runtime_error(message);
}

std::string trim(const std::string &value) {
    const auto first = value.find_first_not_of(" \t\r\n");
    if (first == std::string::npos)
        return {};
    const auto last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

std::string compact(std::string value) {
    value.erase(std::remove_if(value.begin(), value.end(), [](unsigned char ch) {
                    return std::isspace(ch) != 0;
                }),
                value.end());
    return value;
}

std::string lower(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return value;
}

bool file_exists(const std::string &path) {
    struct stat info {};
    return stat(path.c_str(), &info) == 0;
}

std::string parent_path(const std::string &path) {
    const auto separator = path.find_last_of('/');
    if (separator == std::string::npos)
        return ".";
    if (separator == 0)
        return "/";
    return path.substr(0, separator);
}

void create_directories(const std::string &path, mode_t mode) {
    if (path.empty() || path == "/")
        return;
    std::string current;
    if (path.front() == '/')
        current = "/";
    std::stringstream stream(path);
    std::string part;
    while (std::getline(stream, part, '/')) {
        if (part.empty())
            continue;
        if (current.size() > 1)
            current += '/';
        current += part;
        if (mkdir(current.c_str(), mode) != 0 && errno != EEXIST)
            fail("cannot create " + current + ": " + std::strerror(errno));
    }
}

CommandResult run_command(const std::vector<std::string> &arguments) {
    if (arguments.empty())
        fail("empty process command");
    int pipe_fds[2];
    if (pipe(pipe_fds) != 0)
        fail("pipe failed: " + std::string(std::strerror(errno)));

    const pid_t child = fork();
    if (child < 0) {
        close(pipe_fds[0]);
        close(pipe_fds[1]);
        fail("fork failed: " + std::string(std::strerror(errno)));
    }
    if (child == 0) {
        close(pipe_fds[0]);
        dup2(pipe_fds[1], STDOUT_FILENO);
        dup2(pipe_fds[1], STDERR_FILENO);
        close(pipe_fds[1]);
        std::vector<char *> argv;
        argv.reserve(arguments.size() + 1);
        for (const auto &argument : arguments)
            argv.push_back(const_cast<char *>(argument.c_str()));
        argv.push_back(nullptr);
        execvp(argv[0], argv.data());
        _exit(127);
    }

    close(pipe_fds[1]);
    std::string output;
    std::array<char, 4096> buffer {};
    ssize_t count;
    while ((count = read(pipe_fds[0], buffer.data(), buffer.size())) > 0)
        output.append(buffer.data(), static_cast<std::size_t>(count));
    close(pipe_fds[0]);
    int wait_status = 0;
    while (waitpid(child, &wait_status, 0) < 0 && errno == EINTR) {
    }
    int status = -1;
    if (WIFEXITED(wait_status))
        status = WEXITSTATUS(wait_status);
    else if (WIFSIGNALED(wait_status))
        status = 128 + WTERMSIG(wait_status);
    return {status, trim(output)};
}

std::optional<unsigned> whiptail_bandwidth_menu() {
    if (!isatty(STDIN_FILENO) || access("/usr/bin/whiptail", X_OK) != 0)
        return std::nullopt;
    int pipe_fds[2];
    if (pipe(pipe_fds) != 0)
        return std::nullopt;
    const pid_t child = fork();
    if (child < 0) {
        close(pipe_fds[0]);
        close(pipe_fds[1]);
        return std::nullopt;
    }
    if (child == 0) {
        close(pipe_fds[0]);
        // whiptail draws on stdout and returns its selected tag on stderr.
        dup2(STDERR_FILENO, STDOUT_FILENO);
        dup2(pipe_fds[1], STDERR_FILENO);
        close(pipe_fds[1]);
        execl("/usr/bin/whiptail", "whiptail", "--title", "OpenHD RF test",
              "--menu", "Select bandwidth (primary frequency 5180 MHz)",
              "15", "64", "2", "20", "20 MHz", "40", "40 MHz", nullptr);
        _exit(127);
    }
    close(pipe_fds[1]);
    std::string selection;
    std::array<char, 64> buffer {};
    ssize_t count;
    while ((count = read(pipe_fds[0], buffer.data(), buffer.size())) > 0)
        selection.append(buffer.data(), static_cast<std::size_t>(count));
    close(pipe_fds[0]);
    int status = 0;
    while (waitpid(child, &status, 0) < 0 && errno == EINTR) {
    }
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
        fail("RF test bandwidth selection cancelled");
    selection = trim(selection);
    if (selection == "20" || selection == "40")
        return static_cast<unsigned>(std::stoul(selection));
    fail("invalid bandwidth returned by whiptail: " + selection);
}

unsigned select_bandwidth() {
    if (const auto selected = whiptail_bandwidth_menu())
        return *selected;
    std::cout << "Select RF test bandwidth:\n"
                 "  1) 20 MHz (center 5180 MHz)\n"
                 "  2) 40 MHz (primary 5180 MHz, center 5190 MHz)\n"
                 "Selection [1/2]: "
              << std::flush;
    std::string answer;
    std::getline(std::cin, answer);
    if (answer == "1" || answer == "20")
        return 20;
    if (answer == "2" || answer == "40")
        return 40;
    fail("bandwidth selection must be 20 or 40 MHz");
}

std::string real_driver_command(const std::string &interface, const std::string &command) {
    if (interface.size() >= IFNAMSIZ)
        fail("interface name is too long: " + interface);
    if (command.size() >= kIoctlBufferSize)
        fail("driver command is too long");

    std::array<char, kIoctlBufferSize + 1> buffer {};
    std::copy(command.begin(), command.end(), buffer.begin());
    struct ifreq request {};
    union iwreq_data request_data {};
    std::strncpy(request.ifr_name, interface.c_str(), IFNAMSIZ - 1);
    request_data.data.pointer = buffer.data();
    request_data.data.length = kIoctlBufferSize;
    request.ifr_data = reinterpret_cast<char *>(&request_data);

    const int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd < 0)
        fail("socket failed: " + std::string(std::strerror(errno)));
    const int result = ioctl(socket_fd, SIOCDEVPRIVATE, &request);
    const int saved_errno = errno;
    close(socket_fd);
    if (result < 0)
        fail(command + ": " + std::strerror(saved_errno));

    const std::size_t length = std::min<std::size_t>(request_data.data.length, kIoctlBufferSize);
    return trim(std::string(buffer.data(), strnlen(buffer.data(), length)));
}

std::string driver_command(const std::string &interface, const std::string &command) {
    if (command_hook)
        return command_hook(interface, command);
    return real_driver_command(interface, command);
}

std::vector<unsigned char> parse_hex_bytes(const std::string &response) {
    const std::string value = compact(response);
    std::vector<unsigned char> bytes;
    for (std::size_t index = 0; index + 3 < value.size(); ++index) {
        if (value[index] != '0' || (value[index + 1] != 'x' && value[index + 1] != 'X'))
            continue;
        const std::string byte_text = value.substr(index + 2, 2);
        if (!std::isxdigit(static_cast<unsigned char>(byte_text[0])) ||
            !std::isxdigit(static_cast<unsigned char>(byte_text[1])))
            continue;
        bytes.push_back(static_cast<unsigned char>(std::stoul(byte_text, nullptr, 16)));
        index += 3;
    }
    return bytes;
}

Mac parse_mac(const std::string &text) {
    std::string value;
    for (const unsigned char ch : text) {
        if (ch == ':' || ch == '-')
            continue;
        if (!std::isxdigit(ch))
            fail("invalid MAC address: " + text);
        value.push_back(static_cast<char>(ch));
    }
    if (value.size() != 12)
        fail("invalid MAC address: " + text);
    Mac mac {};
    for (std::size_t index = 0; index < mac.size(); ++index)
        mac[index] = static_cast<unsigned char>(std::stoul(value.substr(index * 2, 2), nullptr, 16));
    return mac;
}

std::string format_mac(const Mac &mac, bool separators = true) {
    std::ostringstream output;
    output << std::uppercase << std::hex << std::setfill('0');
    for (std::size_t index = 0; index < mac.size(); ++index) {
        if (separators && index != 0)
            output << ':';
        output << std::setw(2) << static_cast<unsigned>(mac[index]);
    }
    return output.str();
}

bool driver_accepts_mac(const Mac &mac) {
    const Mac zero {};
    Mac ones {};
    ones.fill(0xFF);
    return mac != zero && mac != ones && !(mac[0] & 0x01) && !(mac[0] & 0x02);
}

bool module_mp_enabled() {
    std::ifstream input(std::string("/sys/module/") + kModule + "/parameters/rtw_mp_mode");
    std::string value;
    if (!input || !(input >> value))
        return false;
    return value != "0" && value != "N" && value != "n";
}

std::vector<std::string> driver_interfaces() {
    std::vector<std::string> matches;
    DIR *directory = opendir("/sys/class/net");
    if (!directory)
        fail("cannot inspect /sys/class/net");
    while (const dirent *entry = readdir(directory)) {
        const std::string name = entry->d_name;
        if (name == "." || name == "..")
            continue;
        const std::string link_path = "/sys/class/net/" + name + "/device/driver/module";
        std::array<char, 4096> target {};
        const ssize_t count = readlink(link_path.c_str(), target.data(), target.size() - 1);
        if (count < 0)
            continue;
        target[static_cast<std::size_t>(count)] = '\0';
        std::string resolved(target.data());
        const auto slash = resolved.find_last_of('/');
        if (resolved.substr(slash == std::string::npos ? 0 : slash + 1) == kModule)
            matches.push_back(name);
    }
    closedir(directory);
    std::sort(matches.begin(), matches.end());
    return matches;
}

std::string wait_for_interface(const std::string &preferred, int timeout_seconds = 10) {
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(timeout_seconds);
    while (std::chrono::steady_clock::now() < deadline) {
        const auto matches = driver_interfaces();
        if (std::find(matches.begin(), matches.end(), preferred) != matches.end())
            return preferred;
        if (matches.size() == 1)
            return matches.front();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    fail(std::string("no ") + kModule + " interface appeared after module reload");
}

std::string reload_module(const std::string &requested_interface, bool mp_mode) {
    for (const auto &interface : driver_interfaces())
        run_command({"ip", "link", "set", interface, "down"});
    auto result = run_command({"modprobe", "-r", kModule});
    if (result.status != 0)
        fail(std::string("cannot unload ") + kModule + ": " + result.output);
    std::vector<std::string> arguments{"modprobe", kModule};
    if (mp_mode)
        arguments.emplace_back("rtw_mp_mode=1");
    result = run_command(arguments);
    if (result.status != 0)
        fail(std::string("cannot load ") + kModule + ": " + result.output);
    const std::string interface = wait_for_interface(requested_interface);
    result = run_command({"ip", "link", "set", interface, "up"});
    if (result.status != 0)
        fail("cannot bring " + interface + " up: " + result.output);
    return interface;
}

void ensure_private_file(const std::string &path) {
    struct stat info {};
    if (stat(path.c_str(), &info) != 0)
        fail("required provisioning data is missing: " + path);
    if (!S_ISREG(info.st_mode))
        fail("provisioning data is not a regular file: " + path);
    if (info.st_mode & 0077) {
        std::ostringstream mode;
        mode << std::oct << (info.st_mode & 0777);
        fail(path + " must be root-only (current mode " + mode.str() + ")");
    }
}

std::set<Mac> read_registry(int registry_fd) {
    if (lseek(registry_fd, 0, SEEK_SET) < 0)
        fail("cannot seek MAC registry");
    std::string content;
    std::array<char, 4096> buffer {};
    ssize_t count;
    while ((count = read(registry_fd, buffer.data(), buffer.size())) > 0)
        content.append(buffer.data(), static_cast<std::size_t>(count));
    if (count < 0)
        fail("cannot read MAC registry");
    std::set<Mac> addresses;
    std::istringstream lines(content);
    std::string line;
    while (std::getline(lines, line)) {
        std::istringstream fields(line);
        std::string token;
        if (!(fields >> token))
            continue;
        try {
            addresses.insert(parse_mac(token));
        } catch (const std::exception &) {
        }
    }
    return addresses;
}

Mac allocate_mac(const std::set<Mac> &used) {
    for (unsigned attempt = 0; attempt < 1024; ++attempt) {
        Mac candidate {{kRealtekOui[0], kRealtekOui[1], kRealtekOui[2], 0, 0, 0}};
        if (getrandom(candidate.data() + 3, 3, 0) != 3)
            fail("getrandom failed: " + std::string(std::strerror(errno)));
        if (!used.count(candidate))
            return candidate;
    }
    fail("could not allocate an unused MAC address");
}

Mac read_hardware_mac(const std::string &interface) {
    std::ostringstream command;
    command << "efuse_get rmap," << std::uppercase << std::hex << kMacOffset << ",6";
    const auto bytes = parse_hex_bytes(driver_command(interface, command.str()));
    if (bytes.size() != 6)
        fail("driver returned an invalid MAC readback");
    Mac mac {};
    std::copy(bytes.begin(), bytes.end(), mac.begin());
    return mac;
}

unsigned available_raw_bytes(const std::string &interface) {
    const std::string response = compact(driver_command(interface, "efuse_get ableraw"));
    const auto equals = response.find('=');
    if (equals == std::string::npos)
        fail("cannot parse available eFuse capacity: " + response);
    std::size_t end = equals + 1;
    while (end < response.size() && std::isdigit(static_cast<unsigned char>(response[end])))
        ++end;
    if (end == equals + 1)
        fail("cannot parse available eFuse capacity: " + response);
    return static_cast<unsigned>(std::stoul(response.substr(equals + 1, end - equals - 1)));
}

struct ProvisionResult {
    Mac mac {};
    bool wrote = false;
};

ProvisionResult provision(const std::string &interface, const std::string &map_path,
                          const std::string &mask_path, const Mac &selected_mac,
                          bool assume_yes, const std::function<void(const Mac &)> &reserve_mac) {
    std::string response = driver_command(interface, "mp_start");
    if (lower(compact(response)).find("mp_startok") == std::string::npos)
        fail("MP mode did not start: " + response);

    const Mac current_mac = read_hardware_mac(interface);
    if (driver_accepts_mac(current_mac)) {
        std::cout << "Card is already provisioned with permanent MAC " << format_mac(current_mac)
                  << "; nothing written.\n";
        return {current_mac, false};
    }

    const unsigned available = available_raw_bytes(interface);
    if (available < 256)
        fail("only " + std::to_string(available) + " raw eFuse bytes remain; refusing to program");

    const std::vector<std::pair<std::string, std::string>> staging {
        {"efuse_file " + map_path, "efusefilefile_readok"},
        {"efuse_mask " + mask_path, "efusemaskfilereadok"},
        {"efuse_set wlwfake,157," + format_mac(selected_mac, false), "wlwfakeok"},
    };
    for (const auto &item : staging) {
        response = driver_command(interface, item.first);
        if (lower(compact(response)).find(item.second) == std::string::npos)
            fail("staging failed: " + response);
    }

    std::ostringstream fake_command;
    fake_command << "efuse_get wlrfkrmap," << std::uppercase << std::hex << kMacOffset << ",6";
    const auto fake_bytes = parse_hex_bytes(driver_command(interface, fake_command.str()));
    if (fake_bytes.size() != 6 || !std::equal(fake_bytes.begin(), fake_bytes.end(), selected_mac.begin()))
        fail("fake-map MAC verification failed");

    std::cout << "Interface: " << interface << '\n'
              << "Available raw eFuse capacity: " << available << " bytes\n"
              << "MAC to program: " << format_mac(selected_mac) << '\n';
    if (!assume_yes) {
        std::cout << "This write is irreversible. Type FLASH to continue: " << std::flush;
        std::string answer;
        std::getline(std::cin, answer);
        if (answer != "FLASH")
            fail("cancelled without writing");
    }

    reserve_mac(selected_mac);
    response = driver_command(interface, "efuse_set wlfk2map");
    if (compact(response).find("WiFiwritemapcompareOK") == std::string::npos)
        fail("eFuse write or driver readback failed: " + response);
    const Mac readback = read_hardware_mac(interface);
    if (readback != selected_mac)
        fail("hardware MAC readback failed: read " + format_mac(readback));
    std::cout << "eFuse write and hardware readback succeeded.\n";
    return {selected_mac, true};
}

void check_mp_response(const std::string &command, const std::string &response) {
    const std::string normalized = lower(compact(response));
    if (normalized.find("error") != std::string::npos ||
        normalized.find("fail") != std::string::npos ||
        normalized.find("invalid") != std::string::npos)
        fail(command + " failed: " + response);
}

void stop_signal_handler(int) {
    stop_requested = 1;
}

void transmit_rf_test_signal(const std::string &interface, unsigned bandwidth_mhz,
                             unsigned duration_seconds) {
    if (bandwidth_mhz != 20 && bandwidth_mhz != 40)
        fail("RF test bandwidth must be 20 or 40 MHz");
    stop_requested = 0;
    const auto old_int = std::signal(SIGINT, stop_signal_handler);
    const auto old_term = std::signal(SIGTERM, stop_signal_handler);
    std::string response = driver_command(interface, "mp_start");
    if (lower(compact(response)).find("mp_startok") == std::string::npos)
        fail("MP mode did not start: " + response);

    // Channel 36 has primary frequency 5180 MHz. With 40 MHz bandwidth the
    // secondary channel is above it and the bonded-channel center is 5190 MHz.
    const unsigned bandwidth_code = bandwidth_mhz == 40 ? 1 : 0;
    const unsigned channel_offset = bandwidth_mhz == 40 ? 1 : 0;
    const std::vector<std::string> configuration {
        "mp_ctx stop",
        "mp_rate HTMCS7",
        "mp_ant_tx ab",
        "mp_channel 36",
        "mp_ch_offset " + std::to_string(channel_offset),
        "mp_bandwidth 40M=" + std::to_string(bandwidth_code) + ",shortGI=0",
        "mp_channel 36",
        "mp_bandwidth 40M=" + std::to_string(bandwidth_code) + ",shortGI=0",
        "mp_txpower patha=63,pathb=63",
    };
    for (const auto &command : configuration) {
        response = driver_command(interface, command);
        check_mp_response(command, response);
    }

    std::cout << "Starting maximum-index single-tone RF test:\n"
              << "  primary frequency: 5180 MHz (channel 36)\n"
              << "  bandwidth: " << bandwidth_mhz << " MHz\n"
              << "  power index: 63 on paths A and B\n"
              << "  duration: " << duration_seconds << " seconds\n";
    response = driver_command(interface, "mp_ctx background,stone");
    check_mp_response("mp_ctx background,stone", response);

    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(duration_seconds);
    while (!stop_requested && std::chrono::steady_clock::now() < deadline)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    response = driver_command(interface, "mp_ctx stop");
    check_mp_response("mp_ctx stop", response);
    response = driver_command(interface, "mp_stop");
    check_mp_response("mp_stop", response);
    std::signal(SIGINT, old_int);
    std::signal(SIGTERM, old_term);
    std::cout << "RF test stopped.\n";
}

void reserve_registry_mac(int registry_fd, const Mac &mac) {
    std::ostringstream record;
    record << format_mac(mac) << ' ' << std::time(nullptr) << " reserved\n";
    const std::string text = record.str();
    if (lseek(registry_fd, 0, SEEK_END) < 0 ||
        write(registry_fd, text.data(), text.size()) != static_cast<ssize_t>(text.size()) ||
        fsync(registry_fd) != 0)
        fail("cannot reserve MAC in registry: " + std::string(std::strerror(errno)));
}

void print_help() {
    std::cout << "Usage: openhd-efuse-flash [interface] [--mac MAC] [--yes] [--no-reload]\n"
                 "       openhd-efuse-flash [interface] --rf-test [--bandwidth 20|40]\n\n"
                 "Flash an OpenHD RTL8812EU/RTL8822EU card with a unique persistent MAC.\n\n"
                 "  --mac MAC    use a centrally allocated globally-administered MAC\n"
                 "  --yes        skip the irreversible-write prompt\n"
                 "  --no-reload  require the driver to already be in MP mode\n"
                 "  --rf-test    send a time-bounded maximum-index single-tone test signal\n"
                 "  --bandwidth  select 20 or 40 MHz; otherwise show an interactive menu\n"
                 "  --duration   RF test duration in seconds (default 10, maximum 300)\n";
}

Options parse_options(int argc, char **argv) {
    Options options;
    bool interface_seen = false;
    for (int index = 1; index < argc; ++index) {
        const std::string argument = argv[index];
        if (argument == "-h" || argument == "--help") {
            print_help();
            std::exit(0);
        } else if (argument == "--yes") {
            options.assume_yes = true;
        } else if (argument == "--no-reload") {
            options.no_reload = true;
        } else if (argument == "--self-test") {
            options.self_test = true;
        } else if (argument == "--rf-test") {
            options.rf_test = true;
        } else if (argument == "--mac" || argument == "--map" || argument == "--mask" ||
                   argument == "--registry" || argument == "--bandwidth" ||
                   argument == "--duration") {
            if (++index >= argc)
                fail(argument + " requires a value");
            const std::string value = argv[index];
            if (argument == "--mac")
                options.requested_mac = parse_mac(value);
            else if (argument == "--map")
                options.map_path = value;
            else if (argument == "--mask")
                options.mask_path = value;
            else if (argument == "--bandwidth")
                options.bandwidth_mhz = static_cast<unsigned>(std::stoul(value));
            else if (argument == "--duration") {
                options.duration_seconds = static_cast<unsigned>(std::stoul(value));
                options.duration_set = true;
            }
            else
                options.registry_path = value;
        } else if (!argument.empty() && argument.front() == '-') {
            fail("unknown option: " + argument);
        } else if (!interface_seen) {
            options.interface = argument;
            interface_seen = true;
        } else {
            fail("unexpected argument: " + argument);
        }
    }
    if (options.bandwidth_mhz != 0 && options.bandwidth_mhz != 20 && options.bandwidth_mhz != 40)
        fail("--bandwidth must be 20 or 40");
    if (options.duration_seconds == 0 || options.duration_seconds > 300)
        fail("--duration must be between 1 and 300 seconds");
    if (!options.rf_test && (options.bandwidth_mhz != 0 || options.duration_set))
        fail("--bandwidth and --duration require --rf-test");
    if (options.rf_test && options.requested_mac)
        fail("--mac cannot be combined with --rf-test");
    return options;
}

int self_test() {
    const Mac mac = parse_mac("00:E0:4C:12:34:56");
    if (!driver_accepts_mac(mac) || driver_accepts_mac(parse_mac("02:E0:4C:12:34:56")))
        fail("MAC validation self-test failed");
    unsigned rmap_reads = 0;
    std::vector<std::string> events;
    command_hook = [&](const std::string &, const std::string &command) {
        events.push_back(command);
        if (command == "mp_start")
            return std::string("m p _ s t a r t  o k");
        if (command.rfind("efuse_get rmap", 0) == 0) {
            ++rmap_reads;
            return rmap_reads == 1 ? std::string("0xFF 0xFF 0xFF 0xFF 0xFF 0xFF")
                                   : std::string("0x00 0xE0 0x4C 0x12 0x34 0x56");
        }
        if (command == "efuse_get ableraw")
            return std::string("[ available raw size ] = 1 0 9 0 bytes");
        if (command.rfind("efuse_file ", 0) == 0)
            return std::string("efuse file file_read OK");
        if (command.rfind("efuse_mask ", 0) == 0)
            return std::string("efuse mask file read OK");
        if (command.rfind("efuse_set wlwfake", 0) == 0)
            return std::string("wlwfake OK");
        if (command.rfind("efuse_get wlrfkrmap", 0) == 0)
            return std::string("0x00 0xE0 0x4C 0x12 0x34 0x56");
        if (command == "efuse_set wlfk2map")
            return std::string("WiFi write map compare OK");
        if (command.rfind("mp_", 0) == 0)
            return std::string("OK");
        fail("unexpected self-test command: " + command);
    };
    bool reserved = false;
    const auto result = provision("wlan1", "/map", "/mask", mac, true, [&](const Mac &value) {
        if (value != mac)
            fail("wrong self-test MAC reservation");
        reserved = true;
        events.emplace_back("RESERVED");
    });
    const auto reservation = std::find(events.begin(), events.end(), "RESERVED");
    const auto write_command = std::find(events.begin(), events.end(), "efuse_set wlfk2map");
    if (!result.wrote || result.mac != mac || !reserved || reservation >= write_command)
        fail("blank-card flow self-test failed");
    for (const unsigned bandwidth : {20U, 40U}) {
        events.clear();
        transmit_rf_test_signal("wlan1", bandwidth, 0);
        const std::string bandwidth_command =
            "mp_bandwidth 40M=" + std::to_string(bandwidth == 40 ? 1 : 0) + ",shortGI=0";
        const std::string offset_command = "mp_ch_offset " + std::to_string(bandwidth == 40 ? 1 : 0);
        if (std::find(events.begin(), events.end(), "mp_channel 36") == events.end() ||
            std::find(events.begin(), events.end(), bandwidth_command) == events.end() ||
            std::find(events.begin(), events.end(), offset_command) == events.end() ||
            std::find(events.begin(), events.end(), "mp_txpower patha=63,pathb=63") == events.end() ||
            std::find(events.begin(), events.end(), "mp_ctx background,stone") == events.end() ||
            events.empty() || events.back() != "mp_stop")
            fail(std::to_string(bandwidth) + " MHz RF test command self-test failed");
    }
    command_hook = {};
    std::cout << "Self-test passed.\n";
    return 0;
}

int run(const Options &options) {
    if (options.self_test)
        return self_test();
    if (geteuid() != 0)
        fail("run this tool as root");

    if (options.rf_test) {
        const unsigned bandwidth = options.bandwidth_mhz ? options.bandwidth_mhz : select_bandwidth();
        if (!options.assume_yes) {
            std::cout << "WARNING: This transmits a maximum-index continuous RF single tone.\n"
                         "Use only in a shielded test setup where this transmission is permitted.\n"
                         "Type RF-TEST to continue: "
                      << std::flush;
            std::string answer;
            std::getline(std::cin, answer);
            if (answer != "RF-TEST")
                fail("RF test cancelled");
        }

        create_directories(parent_path(options.registry_path), 0700);
        const int lock_fd = open(options.registry_path.c_str(), O_RDWR | O_CREAT | O_CLOEXEC, 0600);
        if (lock_fd < 0 || flock(lock_fd, LOCK_EX) != 0)
            fail("cannot acquire the provisioning/RF-test lock");
        std::string interface = options.interface;
        const bool restore_normal = !options.no_reload;
        bool normal_mode_restored = false;
        try {
            if (!options.no_reload && !module_mp_enabled()) {
                std::cout << "Reloading " << kModule << " in MP mode...\n";
                interface = reload_module(interface, true);
            } else if (!file_exists("/sys/class/net/" + interface)) {
                interface = wait_for_interface(interface, 2);
            }
            try {
                transmit_rf_test_signal(interface, bandwidth, options.duration_seconds);
            } catch (...) {
                try {
                    driver_command(interface, "mp_ctx stop");
                    driver_command(interface, "mp_stop");
                } catch (const std::exception &error) {
                    std::cerr << "warning: RF stop cleanup failed: " << error.what() << '\n';
                }
                throw;
            }
            if (restore_normal) {
                std::cout << "Reloading " << kModule << " in normal mode...\n";
                interface = reload_module(interface, false);
                normal_mode_restored = true;
            }
        } catch (...) {
            if (restore_normal && !normal_mode_restored) {
                try {
                    interface = reload_module(interface, false);
                } catch (const std::exception &error) {
                    std::cerr << "warning: failed to restore normal driver mode: " << error.what() << '\n';
                }
            }
            close(lock_fd);
            throw;
        }
        close(lock_fd);
        std::cout << "RF test complete on " << interface << ".\n";
        return 0;
    }

    ensure_private_file(options.map_path);
    ensure_private_file(options.mask_path);
    if (options.requested_mac && !driver_accepts_mac(*options.requested_mac))
        fail("the driver requires a globally-administered unicast MAC");

    create_directories(parent_path(options.registry_path), 0700);
    chmod(parent_path(options.registry_path).c_str(), 0700);
    const int registry_fd = open(options.registry_path.c_str(), O_RDWR | O_CREAT | O_CLOEXEC, 0600);
    if (registry_fd < 0)
        fail("cannot open MAC registry: " + std::string(std::strerror(errno)));
    if (flock(registry_fd, LOCK_EX) != 0) {
        close(registry_fd);
        fail("cannot lock MAC registry");
    }

    try {
        const auto used = read_registry(registry_fd);
        const Mac selected_mac = options.requested_mac ? *options.requested_mac : allocate_mac(used);
        if (used.count(selected_mac))
            fail("MAC " + format_mac(selected_mac) + " is already in the registry");

        std::string interface = options.interface;
        const bool restore_normal = !options.no_reload;
        if (!options.no_reload && !module_mp_enabled()) {
            std::cout << "Reloading " << kModule << " in MP mode...\n";
            interface = reload_module(interface, true);
        } else if (!file_exists("/sys/class/net/" + interface)) {
            interface = wait_for_interface(interface, 2);
        }

        try {
            provision(interface, options.map_path, options.mask_path, selected_mac,
                      options.assume_yes,
                      [&](const Mac &mac) { reserve_registry_mac(registry_fd, mac); });
        } catch (...) {
            if (restore_normal) {
                std::cerr << "Reloading " << kModule << " in normal mode...\n";
                try {
                    interface = reload_module(interface, false);
                } catch (const std::exception &error) {
                    std::cerr << "warning: failed to restore normal driver mode: " << error.what() << '\n';
                }
            }
            throw;
        }

        if (restore_normal) {
            std::cout << "Reloading " << kModule << " in normal mode...\n";
            interface = reload_module(interface, false);
        }
        const auto permanent = run_command({"ethtool", "-P", interface});
        if (permanent.status == 0)
            std::cout << permanent.output << '\n';
        std::cout << "Provisioning complete on " << interface << ".\n";
    } catch (...) {
        close(registry_fd);
        throw;
    }
    close(registry_fd);
    return 0;
}

} // namespace

int main(int argc, char **argv) {
    try {
        return run(parse_options(argc, argv));
    } catch (const std::exception &error) {
        std::cerr << "error: " << error.what() << '\n';
        return 1;
    }
}
