#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    while (true) {
        std::cout << "mini-shell> ";
        std::string line;
        if (!std::getline(std::cin, line)) break;

        std::vector<char*> args;
        char* token = strtok(const_cast<char*>(line.c_str()), " ");
        while (token) {
            args.push_back(token);
            token = strtok(nullptr, " ");
        }
        args.push_back(nullptr);

        if (args[0] == nullptr) continue;
        if (std::string(args[0]) == "exit") break;

        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args.data());
            std::cerr << "Command not found\n";
            _exit(1);
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
        } else {
            std::cerr << "Fork failed\n";
        }
    }
    std::cout << "END\n";
    return 0;
}

