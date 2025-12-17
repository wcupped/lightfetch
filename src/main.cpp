#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <limits.h>
#include <fstream>
#include <memory>
#include <array>
#include <sys/sysinfo.h>
#include <vector>
#include <ctime>

std::string get_pretty_name();
std::string cmd_output(const char* cmd);
void show_help_func();

int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(0);

    bool joke = false;

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--help" || std::string(argv[i]) == "-h") {
            show_help_func();
            return 0;
        }
        else if (std::string(argv[i]) == "--joke" || std::string(argv[i]) == "-j") {
            joke = true;
        }
    }

    std::srand(std::time(nullptr));
    std::vector<std::string> dumb_jokes = {
        "brain just segfaulted",
        "Bailing out, you are on your own. Good luck",
        "try fastfetch instead",
        "i use lightfetch btw"
    };

    struct sysinfo info;
    char hostname[HOST_NAME_MAX];
    std::string distro_name = get_pretty_name();

    std::cout << std::getenv("USER") << "@";

    if (gethostname(hostname, HOST_NAME_MAX) == 0) {
        std::cout << hostname << '\n';
    } else {
        std::cout << "Failed to get hostname\n";
    }

    for (int i = 0; i < 20; ++i) std::cout << "-";
    std::cout << '\n';
    
    std::cout << "OS: " << distro_name << '\n';
    std::cout << "Kernel: Linux " << cmd_output("uname -r");
    std::cout << "Shell: " << std::getenv("SHELL") << '\n';
    std::cout << "Uptime: ";
    if (sysinfo(&info) == 0) {
        int hours = info.uptime / 3600;
        int remaining = info.uptime % 3600;
        int minutes = remaining / 60;
        int seconds = remaining % 60;

        std::cout << hours << "h" << minutes << "m" << seconds << "s\n";
    }
    
    std::cout << "Terminal: " << std::getenv("TERM") << '\n';
    std::cout << "DE/WM: " << std::getenv("XDG_CURRENT_DESKTOP") << '\n';

    if (joke) {
        std::cout << dumb_jokes[std::rand() % dumb_jokes.size()] << '\n';
    }
    
    return 0;
}

std::string get_pretty_name() {
    std::ifstream file("/etc/os-release");
    std::string line, key = "PRETTY_NAME=";
    while (std::getline(file, line)) {
        if (line.find(key) == 0) {
            std::string val = line.substr(key.length());
            if (!val.empty() && (val.front() == '"' || val.front() == '\''))
                 val = val.substr(1, val.length() - 2);
            return val;
        }
    }
    return "Linux";
}


std::string cmd_output(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    
    FILE* pipe = popen(cmd, "r");
    if (!pipe) {
        return "popen() failed!";
    }
    
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }
    
    pclose(pipe);
    return result;
}

void show_help_func() {
    std::cout << "Usage: lightfetch [options]\n\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help    Show this help and exit\n";
    std::cout << "  -j, --joke    Don't show joke at the last line.\n";
}
