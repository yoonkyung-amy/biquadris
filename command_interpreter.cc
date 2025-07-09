#include "command_interpreter.h"

#include <utility>

// REQUIRES:
//    command must not be empty string
std::pair<std::string, int> Command_interpreter::readCommand(std::string &command, std::vector<std::string> commands) {
    if (command.empty()) throw std::invalid_argument{"Command is not found, please try again."}; // This implies system error
    std::pair<std::string, int> return_val;
    std::string number_string;
    int char_idx = 0;
    for (char *c = &command[0]; *c; c++) {
        if (*c < '0' || *c > '9') break;
        number_string += *c;
        char_idx++;
    }
    return_val.second = (number_string.empty() ? 1 : std::stoi(number_string));

    int idx = 0;
    for (char *c = &command[char_idx]; *c; c++) {
        for (int i = 0; i < commands.size();) {
            if (commands[i][idx] != *c) {
                commands.erase(commands.begin() + i);
            } else {
                i++;
            }
        }
        idx++;
    }
    if (commands.empty()) throw no_matching_found{"No matching command is found, please try again."};
    else if (commands.size() == 1) {
        return_val.first = commands[0];
        return return_val;
    } else {
        for (int i = 0; i < commands.size(); i++) {
            if (commands[i][idx] == '\0') {
                return_val.first = commands[i];
                return return_val;
            }
        }
        std::string list;
        for (int i = 0; i < commands.size(); i++) {
            if (i != 0) list += ", ";
            list += commands[i];
        }
        throw no_matching_found{"Command is incomplete, please try again\n[TIP] Consider: " + list};
    }
}

no_matching_found::no_matching_found(std::string msg) : msg{std::move(msg)} {}

std::string no_matching_found::what() const noexcept {
    return msg;
}
