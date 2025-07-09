#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include "command_interpreter.h"
#include "terminal.h"

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

int main(int argc, char *argv[]) {

    std::string cmd;
    std::string set_seed;
    std::string starting_level;
    std::string file_1 = "sequence1.txt"; // by default
    std::string file_2 = "sequence2.txt";
    std::ifstream reader;
    bool read_from_file = false;
    int level = 0;
    int seed = -1;
    bool graphic = true;
    int i = 1;

    // Command-line interface
    while (i < argc) {
        cmd = argv[i];

        if (cmd == "-text") {
            graphic = false;
        } else if (cmd == "-seed") {
            set_seed = argv[++i];
            seed = stoi(set_seed);
            // possible exceptions?
            // srand(seed);
        } else if (cmd == "-scriptfile1") {
            // TODO: check if ++i is even valid by using argc
            // we need to make sure ++i is valid and it is what we want
            // (i.e., -scriptfile1 -scriptfile2 xxx2.txt makes ++i valid but option is not?)
            if (i + 1 < argc) {
                file_1 = argv[++i];
            }
        } else if (cmd == "-scriptfile2") {
            if (i + 1 < argc) {
                file_2 = argv[++i];
            }
        } else if (cmd == "-startlevel") {
            starting_level = argv[++i];
            try {
                level = stoi(starting_level);
            } catch (std::exception &err) {
                std::cerr << err.what() << std::endl;
            }
        } else {
            // Not Valid command line?
        }
        ++i;
    }



    Terminal *biquadris = new Terminal{file_1, file_2, seed, level, graphic};

    // Command Interpreter
    std::string CI;
    std::vector<std::string> commandList = {"left", "right", "down", "drop", "counterclockwise", "clockwise",
                                         "levelup", "leveldown", "norandom", "random", "sequence",
                                         "restart", "I", "J", "S", "Z", "L", "O", "T"};

    while (true) {
        if (read_from_file) {
            reader >> CI;
            if (reader.eof()) {
                read_from_file = false;
                reader.close();
            }
        }
        if (!read_from_file) {
            std::cin >> CI;
            if (std::cin.fail()) {
                std::cout << "Program ended" << std::endl;
                std::cin.ignore();
                std::cin.clear();
                break;
            }
        }
        std::pair<std::string, int> result;
        try {
            result = Command_interpreter::readCommand(CI, commandList);
        } catch (std::invalid_argument &e) {
            // System error that occurs when CI is empty string (should never happen)
            std::cerr << e.what() << std::endl; // err stream
            continue;
        } catch (std::out_of_range &e) {
            // happens when the user input has number exceeding the int data's limit
            std::cerr << "Given number is too large, please try again." << std::endl;
            continue;
        } catch (no_matching_found &e) {
            // occurs when the command is not valid and prints the problem to the user
            std::cout << e.what() << std::endl; // out steam
            continue;
        }

        if (result.first == "left") {
            biquadris->left(result.second);
        } else if (result.first == "right") {
            biquadris->right(result.second);
        } else if (result.first == "down") {
            biquadris->down(result.second);
        } else if (result.first == "clockwise") {
            biquadris->clockwise(result.second);
        } else if (result.first == "counterclockwise") {
            biquadris->counter_clockwise(result.second);
        } else if (result.first == "drop") {
            biquadris->drop(result.second);
        } else if (result.first == "levelup") {
            biquadris->level_up(result.second);
        } else if (result.first == "leveldown") {
            biquadris->level_down(result.second);
        } else if (result.first == "norandom") {
            std::string file_name;
            if (read_from_file) {
                reader >> file_name;
                if (reader.eof()) {
                    read_from_file = false;
                    reader.close();
                }
            }
            if (!read_from_file) {
                std::cin >> file_name;
            }
            biquadris->noRandom(file_name);
        } else if (result.first == "random") {
            biquadris->random();
        } else if (result.first == "sequence") {
            // TODO: Sequence
            std::string file_name;
            if (read_from_file) {
                reader >> file_name;
                if (reader.eof()) {
                    read_from_file = false;
                    reader.close();
                }
            }
            if (!read_from_file) {
                std::cin >> file_name;
            }
            try {
                reader.open(file_name);
            } catch (std::exception &e) {
                std::cerr << "file is not available" << std::endl;
            }
            read_from_file = true;
            //...
        } else if (result.first == "I" || result.first == "J" || result.first == "L" ||
                   result.first == "O" || result.first == "S" || result.first == "Z" || result.first == "T") {
            char c = result.first[0];
            biquadris->change(c);
        } else if (result.first == "restart") {
            biquadris->restart();
        } else {
            continue;
        }
    }

    delete biquadris;

}













