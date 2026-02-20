#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <limits.h>
#include <fstream>
#include <memory>
#include <array>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <vector>
#include <ctime>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */

std::string get_pretty_name();
// std::string cmd_output(const char* cmd);
void show_help_func();
bool is_env_null(const char* env_name);

int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(0);

    bool joke = false;

    // parsing arguments
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--help" || std::string(argv[i]) == "-h") {
            show_help_func();
            return 0;
        }
        else if (std::string(argv[i]) == "--joke" || std::string(argv[i]) == "-j") {
            joke = true;
        }
    }

    // seeding random
    std::srand(std::time(nullptr));
    // vector array of dumb jokes
    constexpr const char* dumb_jokes[] = {
        "brain just segfaulted",
        "Bailing out, you are on your own. Good luck",
        "try fastfetch instead",
        "i use lightfetch btw",
        "don't mind using neofetch, it's outdated",
        "The more if, then else elif"
    };
    
    constexpr size_t jokes_count = sizeof(dumb_jokes) / sizeof(dumb_jokes[0]);

    struct sysinfo info;
    struct utsname unameData;
    char hostname[HOST_NAME_MAX];
    std::string distro_name = get_pretty_name();

    uname(&unameData);

    if (uname(&unameData) != 0) {
        std::cerr << RED << "uname() failed.\n";
    }

    std::cout << BOLDCYAN;
    if (!is_env_null("USER"))
        std::cout << std::getenv("USER");
    else
        std::cout << "Unknown";
    std::cout << "@";

    if (gethostname(hostname, HOST_NAME_MAX) == 0) {
        std::cout << hostname << '\n';
    } else {
        std::cout << RED << "Failed to get hostname\n";
    }

    std::cout << WHITE << std::string(20, '-') << '\n';
    
    std::cout << BLUE << "OS: " << GREEN << distro_name << '\n';
    // cmd_output("uname -r") is less secure than uname() from sys/utsname.h
    // std::cout << "Kernel: Linux " << cmd_output("uname -r");
    std::cout << BLUE "Kernel: " << GREEN << "Linux " << unameData.release << '\n';
    std::cout << BLUE << "Shell: " << GREEN;
    if (!is_env_null("SHELL"))
        std::cout << std::getenv("SHELL") << '\n';
    else
        std::cout << RED << "Failed to get shell\n";
    std::cout << BLUE << "Uptime: " << GREEN;

    if (sysinfo(&info) == 0) {
        int hours = info.uptime / 3600;
        int remaining = info.uptime % 3600;
        int minutes = remaining / 60;
        int seconds = remaining % 60;

        std::cout << hours << "h" << minutes << "m" << seconds << "s\n";
    }
    
    std::cout << BLUE << "Terminal: " << GREEN;
    if (!is_env_null("TERM"))
        std::cout << std::getenv("TERM") << '\n';
    else
        std::cout << RED << "Failed to get terminal\n";
    std::cout << BLUE << "DE/WM: " << GREEN;
    if (!is_env_null("XDG_CURRENT_DESKTOP"))
        std::cout << std::getenv("XDG_CURRENT_DESKTOP") << '\n';
    else
        std::cout << RED << "Failed to get current desktop\n";

    // printing one of dumb jokes if joke flag is set.
    if (joke) {
        std::cout << YELLOW << dumb_jokes[std::rand() % jokes_count] << '\n';
    }
    
    return 0;
}

// function to get pretty name of system from /etc/os-release file
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

// removed: using sys/utsname.h instead
/*std::string cmd_output(const char* cmd) {
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
*/

// pretty obvious, function to show help text
void show_help_func() {
    std::cout << "Usage: lightfetch [options]\n\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help    Show this help and exit\n";
    std::cout << "  -j, --joke    Shows a joke at the last line of all info.\n";
}

// function to check if environment variable is nullptr or not
bool is_env_null(const char* env_name) {
    bool result;
    if (std::getenv(env_name) == nullptr)
        result = true;
    else
        result = false;

    return result;
}
