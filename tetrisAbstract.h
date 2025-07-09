#ifndef __TETRIS_ABSTRACT_H__
#define __TETRIS_ABSTRACT_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "grid.h"

class TetrisAbstract {
public:
    virtual ~TetrisAbstract();
    virtual bool right(int step) = 0;
    virtual bool left(int step) = 0;
    virtual bool down(int step) = 0;
    virtual void clockwise(int step) = 0;
    virtual void counter_clockwise(int step) = 0;
    virtual bool drop(int step) = 0;
    virtual Grid *getGrid() = 0;
    virtual int getScore() = 0;
    virtual int getNextLevel() = 0;
    virtual void level_up(int step) = 0;
    virtual void level_down(int step) = 0;
    virtual void random() = 0;
    virtual void noRandom(const std::string &sequence_file) = 0;
    virtual void changeCurrentBlock(BlockShape type) = 0;
    virtual bool isHeavy() = 0;
    virtual std::vector<std::pair<int,int>> getNextShape() = 0;
    virtual Block *getNextBlock() = 0;
    virtual void setBlind(bool _blind) = 0;
    virtual bool isBlind() = 0;
    virtual bool isOver() = 0;
};

#endif
