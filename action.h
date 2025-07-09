#ifndef TEST4_ACTION_H
#define TEST4_ACTION_H

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

enum class Action {
    updateCurrent,
    updateNext,
    reset,
    blind,
    score
};

#endif //TEST4_ACTION_H
