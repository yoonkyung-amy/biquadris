#include "tetris.h"

Tetris::Tetris(std::string standard_sequence, int seed, int initial_level, int width, int height, int reserved) :
standard_sequence{standard_sequence},
current_level{initial_level},
next_level{current_level},
reserved{reserved},
grid{new Grid{width, height}},
current_block{nullptr},
next_block{nullptr},
score{0},
game_over{false},
seed{seed} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Tetris Constructor" << std::endl;
#endif
    // map every block shape with its corresponding block dispenser
    dispenser.insert(std::pair<BlockShape, BlockDispenser*>(BlockShape::I, new BlockDispenser_I{grid}));
    dispenser.insert(std::pair<BlockShape, BlockDispenser*>(BlockShape::J, new BlockDispenser_J{grid}));
    dispenser.insert(std::pair<BlockShape, BlockDispenser*>(BlockShape::L, new BlockDispenser_L{grid}));
    dispenser.insert(std::pair<BlockShape, BlockDispenser*>(BlockShape::O, new BlockDispenser_O{grid}));
    dispenser.insert(std::pair<BlockShape, BlockDispenser*>(BlockShape::S, new BlockDispenser_S{grid}));
    dispenser.insert(std::pair<BlockShape, BlockDispenser*>(BlockShape::Z, new BlockDispenser_Z{grid}));
    dispenser.insert(std::pair<BlockShape, BlockDispenser*>(BlockShape::T, new BlockDispenser_T{grid}));
    dispenser.insert(std::pair<BlockShape, BlockDispenser*>(BlockShape::TINY, new BlockDispenser_tiny{grid}));
    // add levels
    levels.push_back(new Level_0{standard_sequence, seed});
    levels.push_back(new Level_1{standard_sequence, seed});
    levels.push_back(new Level_2{standard_sequence, seed});
    levels.push_back(new Level_3{standard_sequence, seed});
    levels.push_back(new Level_4{standard_sequence, seed});
    // set maximum level
    maximum_level = levels.size() - 1;
    // apply level
    levelObj = levels[current_level];
    // set blocks
    next_block = dispenser[levelObj->getNextBlock()]->getBlock(current_level);
    blocks.push_back(next_block);
    updateBlock();

}

void Tetris::gameOver() {
    game_over = true;
    // TODO: notify the observers
    std::cout << "game over" << std::endl;
}

void Tetris::updateBlock() {
    current_block = next_block;
    bool is_game_over = current_block->placeAt(reserved, 0);
    if (is_game_over) {
        gameOver();
    }
    next_block = dispenser[levelObj->getNextBlock()]->getBlock(current_level);
    blocks.push_back(next_block);
}

Tetris::~Tetris() {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Tetris Destructor" << std::endl;
#endif
    current_block = nullptr;
    next_block = nullptr;
    BlockShapeUtil block_shape_util;
    std::vector<BlockShape> shape_list = block_shape_util.getBlockList();
    for (BlockShape &shape : shape_list) {
        delete dispenser[shape];
    }
    for (int i = 0; i < levels.size(); i++) {
        delete levels[i];
    }
    for (auto &block : blocks) {
        delete block;
    }
    delete grid;
}

Block *Tetris::get_current_block() const noexcept {
    return current_block;
}

Grid *Tetris::getGrid() {
    return grid;
}

int Tetris::getScore() {
    return score;
}

int Tetris::getNextLevel() {
    return next_level;
}

void Tetris::setBlind(bool _blind) {
    blind = _blind;
}

bool Tetris::isBlind() {
    return blind;
}

void Tetris::placeTiny() {
    Block *tiny = dispenser[BlockShape::TINY]->getBlock(current_level);
    int row = 0;
    int col = grid->getWidth()/2;
    blocks.push_back(tiny);
    tiny->placeAt(row, col);
    tiny->drop();
}

bool Tetris::right(int step) {
    try {
        current_block->right(step);
    } catch (InvalidActionException &err) {
        std::cerr << err.what() << std::endl;
    }
    levelObj->action_right(this);
    return true;
}

bool Tetris::left(int step) {
    try {
        current_block->left(step);
    } catch (InvalidActionException &err) {
        std::cerr << err.what() << std::endl;
    }
    levelObj->action_left(this);
    return true;
}

bool Tetris::down(int step) {
    bool moved;
    try {
        moved = current_block->down(step);
    } catch (InvalidActionException &err) {
        std::cerr << err.what() << std::endl;
    }
    levelObj->action_down(this);
    return moved;
}

bool Tetris::drop(int step) {
    int cleared = 0;
    for (int counter = 0; counter < step; counter++) {
        current_block->drop();
        std::vector < Block * > existing;
        for (int row = 0; row < grid->getHeight(); row++) {
            for (int col = 0; col < grid->getWidth(); col++) {
                bool found = false;
                for (int i = 0; i < existing.size(); i++) {
                    if (existing[i] == grid->getBoard(row, col)) found = true;
                }
                if (!found) {
                    existing.push_back(grid->getBoard(row, col));
                }
            }
        }
        cleared = grid->dropped();
        for (int row = 0; row < grid->getHeight(); row++) {
            for (int col = 0; col < grid->getWidth(); col++) {
                for (int i = 0; i < existing.size(); i++) {
                    if (existing[i] == grid->getBoard(row, col)) {
                        existing.erase(existing.begin() + i);
                    }
                }
            }
        }
        // count score
        if (cleared > 0) {
            score += (current_level + cleared) * (current_level + cleared);
            for (int i = 0; i < existing.size(); i++) {
                score += (existing[i]->getLevel() + 1) * (existing[i]->getLevel() + 1);
            }
        }
        // set next level
        levelObj->action_drop(this, cleared);
        current_level = next_level;
        levelObj = levels[current_level];
        // update the next block
        updateBlock();
        if (game_over) break;
    }
    // if more than 1 row is cleared, special action triggered
    if (cleared > 1 && !game_over) {
        return true;
    } else {
        return false;
    }
}

void Tetris::clockwise(int step) {
    try {
        current_block->clockwise(step);
    } catch (InvalidActionException &err) {
        std::cerr << err.what() << std::endl;
    }
    levelObj->action_clockwise(this);
}

void Tetris::counter_clockwise(int step) {
    try {
        current_block->counter_clockwise(step);
    } catch (InvalidActionException &err) {
        std::cerr << err.what() << std::endl;
    }
    levelObj->action_counter_clockwise(this);
}

void Tetris::level_up(int step) {
    if (step < 0) return;
    next_level += step;
    if (next_level > maximum_level) next_level = maximum_level;
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i] == next_block) {
            blocks.erase(blocks.begin() + i);
            break;
        }
    }
    delete next_block;
    next_block = dispenser[levels[next_level]->getNextBlock()]->getBlock(next_level);
}

void Tetris::level_down(int step) {
    if (step < 0) return;
    next_level -= step;
    if (next_level < 0) next_level = 0;
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i] == next_block) {
            blocks.erase(blocks.begin() + i);
            break;
        }
    }
    delete next_block;
    next_block = dispenser[levels[next_level]->getNextBlock()]->getBlock(next_level);
}

void Tetris::random() {
    levelObj->random();
}

void Tetris::noRandom(const std::string &sequence_file) {
    levelObj->noRandom(sequence_file);
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i] == next_block) {
            blocks.erase(blocks.begin() + i);
            break;
        }
    }
    delete next_block;
    next_block = dispenser[levelObj->getNextBlock()]->getBlock(current_level);
}

void Tetris::changeCurrentBlock(BlockShape type) {
    for (int row = 0; row < grid->getHeight(); row++) {
        for (int col = 0; col < grid->getWidth(); col++) {
            if (grid->getBoard(row, col) == current_block) {
                grid->setBoard(row, col, nullptr);
            }
        }
    }
//    for (int i = 0; i < blocks.size(); i++) {
//        if (blocks[i] == current_block) {
//            blocks.erase(blocks.begin() + i);
//            break;
//        }
//    }
//    delete current_block;
    current_block = dispenser[type]->getBlock(current_level);
    blocks.push_back(current_block);
    bool is_game_over = current_block->placeAt(reserved, 0);
    if (is_game_over) {
        gameOver();
    }
}

bool Tetris::isHeavy() {
    return false;
}

bool Tetris::isOver() {
    return game_over;
}
