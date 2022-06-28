#include <cstdio>
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

inline std::string capture_call(const char* cmd) { // this function captures the shell's output for command `cmd`
    // capture both stdout and stderr
    std::string cmd2 = cmd + std::string(" 2>&1");

    // start the process
    FILE* f = popen(cmd2.data(), "r");

    // can't seek within this stream, so read in a KB at a time.
    std::vector<char> vec;
    char line[1024];
    size_t count = 0;
    do {
        count = fread(line, 1, 1024, f);
        vec.insert(vec.end(), line, line + count);
    } while(1024 == count);

    // build output string
    std::string s(vec.begin(), vec.end());

    // if the process ends unsuccessfully (i.e. a non-zero exit code), throw an exception
    if (pclose(f)) {
        throw std::runtime_error(s);
    }

    // output the shell's output
    return s;
}

inline std::string git_version() {
    // get current git's commit hash
    return capture_call("git rev-parse HEAD");
}

int main() {
    // print using std::cout
    std::cout << git_version();

    // convert to a string literal and then print out
    puts(@string(git_version().c_str()));

    // return
    return 0;
}
