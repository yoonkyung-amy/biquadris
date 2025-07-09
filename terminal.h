#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "userInterface.h"

class Terminal {
    UserInterface *ui;
    bool isGraphicOn;
    int seed;

public:
    Terminal(const std::string &seq1, const std::string &seq2, int seed, int initial_level = 0, bool isGraphicOn = true);
    ~Terminal();

    void left(int step);
    void right(int step);
    void down(int step);
    void clockwise(int step);
    void counter_clockwise(int step);
    void drop(int step);
    void level_up(int step);
    void level_down(int step);
    void noRandom(const std::string &file);
    void random();
    void change(char type);
    void restart();
    void setGraphic(bool);
};

#endif
