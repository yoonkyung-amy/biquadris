// This is interface of Tetris class
#ifndef __TETRIS_H__
#define __TETRIS_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "tetrisAbstract.h"
#include "sequence.h"
#include "grid.h"
#include "blockDispenser_I.h"
#include "blockDispenser_J.h"
#include "blockDispenser_L.h"
#include "blockDispenser_O.h"
#include "blockDispenser_S.h"
#include "blockDispenser_Z.h"
#include "blockDispenser_T.h"
#include "blockDispenser_tiny.h"
#include "blockShape.h"
#include "level_0.h"
#include "level_1.h"
#include "level_2.h"
#include "level_3.h"
#include "level_4.h"
#include <vector>
#include <map>
#include <iomanip>

class Tetris : public TetrisAbstract {
    std::string standard_sequence;
    int current_level;
    int next_level;
    const int reserved;
    Grid *grid;
    std::vector<Block*> blocks;
    Block *current_block;
    Block *next_block;
    std::map<BlockShape, BlockDispenser*> dispenser;
    std::vector<Level*> levels;
    Level *levelObj;
    int maximum_level;
    int score;
    bool game_over;
    int seed;
    bool blind = false;

    void gameOver();
    void updateBlock();
public:

    explicit Tetris(std::string standard_sequence, int seed, int initial_level = 0, int width = 11, int height = 18, int reserved = 3);
    virtual ~Tetris();

    Block *get_current_block() const noexcept;

    void placeTiny();

    Grid *getGrid() override;

    int getScore() override;

    int getNextLevel() override;

    void setBlind(bool _blind) override;

    bool isBlind() override;

    bool right(int step) override;

    bool left(int step) override;

    bool down(int step) override;

    bool drop(int step) override;

    void clockwise(int step) override;

    void counter_clockwise(int step) override;

    void level_up(int step) override;

    void level_down(int step) override;

    void random() override;

    void noRandom(const std::string &sequence_file) override;

    void changeCurrentBlock(BlockShape type) override;

    bool isHeavy() override;

    std::vector<std::pair<int,int>> getNextShape() override {
        return next_block->getShape();
    }

    Block *getNextBlock() override {
        return next_block;
    }

    void printGrid() {
        BlockShapeUtil util;
        std::cout << "Level:" << std::setfill(' ') << std::setw(5) << next_level << std::endl;
        std::cout << "Score:" << std::setfill(' ') << std::setw(5) << score << std::endl;
        for (int col = 0; col < grid->getWidth(); col++) {
            std::cout << "-";
        }
        std::cout << std::endl;
        for (int row = 0; row < grid->getHeight(); row++) {
            for (int col = 0; col < grid->getWidth(); col++) {
                if (grid->getBoard(row,col) == nullptr) {
                    std::cout << ".";
                } else {
                    std::cout << util.to_char(grid->getBoard(row,col)->getType());
                }
            }
            std::cout << std::endl;
        }
        for (int col = 0; col < grid->getWidth(); col++) {
            std::cout << "-";
        }
        std::cout << "\nNext:" <<std::endl;
        auto shape = next_block->getShape();
        for (int row = 1; row >= 0; row--) {
            for (int col = 0; col < grid->getWidth(); col++) {
                bool found = false;
                for (int i = 0; i < shape.size(); i++) {
                    if (shape[i].first == row && shape[i].second == col) {
                        found = true;
                    }
                }
                if (found) {
                    std::cout << util.to_char(next_block->getType());
                } else {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    bool isOver() override;
};

#endif
