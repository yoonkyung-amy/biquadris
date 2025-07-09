#ifndef __COMMAND_INTERPRETER_H__
#define __COMMAND_INTERPRETER_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include <string>
#include <vector>
#include <stdexcept>

class Command_interpreter {
public:
    static std::pair<std::string, int> readCommand(std::string &command, std::vector<std::string> commands);
};

class no_matching_found {
    std::string msg;
public:
    explicit no_matching_found(std::string msg);
    std::string what() const noexcept;
};

#endif
