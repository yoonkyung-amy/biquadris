#ifndef __HEAVY_H__
#define __HEAVY_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "tetrisDecorator.h"

class Heavy : public TetrisDecorator {
    const int heaviness;
public:
    Heavy(TetrisAbstract *component, int heaviness);
    ~Heavy() {
#if DEBUG_LEVEL > 0
        #include <iostream>
    std::cout << "Heavy Destructor" << std::endl;
#endif
    }
    bool right(int step) override;
    bool left(int step) override;
    bool down(int step) override;
    void clockwise(int step) override;
    void counter_clockwise(int step) override;
    bool drop(int step) override;
    Grid *getGrid() override;
    int getScore() override;
    int getNextLevel() override;
    void level_up(int step) override;
    void level_down(int step) override;
    void random() override;
    void noRandom(const std::string &sequence_file) override;
    void changeCurrentBlock(BlockShape type) override;
    bool isHeavy() override;
    void setBlind(bool _blind) override;
    bool isBlind() override;
    std::vector<std::pair<int,int>> getNextShape() override;
    Block *getNextBlock() override;
    bool isOver() override;
};

#endif
