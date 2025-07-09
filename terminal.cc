#include "terminal.h"
#include "command_interpreter.h"
#include "blockShape.h"
#include "userInterface.h"
#include "subject.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

Terminal::Terminal(const std::string &seq1, const std::string &seq2, int seed, int initial_level, bool isGraphicOn) {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Teriminal Constructor" << std::endl;
#endif
    std::vector<std::string> sequences;
    sequences.push_back(seq1);
    sequences.push_back(seq2);
    ui = new UserInterface{sequences, seed, initial_level, isGraphicOn};

}

Terminal::~Terminal() {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Terminal Destructor" << std::endl;
#endif
    if (ui != nullptr) {
        delete ui;
    }
}

void Terminal::left(int step) {
    ui->left(step);
}

void Terminal::right(int step) {
    ui->right(step);
}

void Terminal::down(int step) {
    ui->down(step);
}

void Terminal::clockwise(int step) {
    ui->clockwise(step);
}

void Terminal::counter_clockwise(int step) {
    ui->counter_Clockwise(step);
}

void Terminal::drop(int step) {
    bool special_action = ui->drop(step);
    if (special_action) {
        std::cout << "Special action is available: blind, heavy, force <block>" << std::endl;
        std::vector<std::string> actions = {"blind", "heavy", "force"};
        std::string command;
        while (std::cin >> command) {
            std::pair<std::string, int> result;
            try {
                result = Command_interpreter::readCommand(command, actions);
            } catch (std::invalid_argument &e) {
                // System error that occurs when CI is empty string (should never happen)
                std::cerr << e.what() << std::endl; // err stream
                continue;
            } catch (no_matching_found &e) {
                // occurs when the command is not valid and prints the problem to the user
                std::cout << e.what() << std::endl; // out steam
                continue;
            }

            if (result.first == "blind") {
                ui->apply_blind();
            } else if (result.first == "heavy") {
                ui->apply_heavy();
            } else if (result.first == "force") {
                BlockShapeUtil util;
                BlockShape type;
                char temp;
                std::cin >> temp;
                try {
                    type = util.to_block_shape(temp);
                } catch (InvalidSymbolicCharException &e) {
                    std::cout << "Given block is not found, please try again" << std::endl;
                    continue;
                }
                if (type == BlockShape::TINY) {
                    std::cout << "Given block is not found, please try again" << std::endl;
                    continue;
                }
                ui->apply_force(type);
            }
            break;
        }
    }
}

void Terminal::level_up(int step) {
    ui->level_up(step);
}

void Terminal::level_down(int step) {
    ui->level_down(step);
}

void Terminal::noRandom(const std::string &file) {
    ui->noRandom(file);
}

void Terminal::random() {
    ui->random();
}

void Terminal::change(char type) {
    BlockShapeUtil util;
    BlockShape temp;
    try {
        temp = util.to_block_shape(type);
    } catch (InvalidSymbolicCharException &err) {
        err.printException();
        return;
    }
    ui->change(temp);
}

void Terminal::restart() {
    ui->restart();
}

void Terminal::setGraphic(bool graphic) {
    ui->setGraphic(graphic);
}
