#include "level_4.h"
#include "blockShape.h"
#include "tetris.h"
#include <vector>
#include <cstdlib>

Level_4::Level_4(const std::string &standard_sequence_file, int seed) :
        Level{standard_sequence_file, true, seed},
        counter{0} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Level_4 Constructor" << std::endl;
#endif
}

BlockShape Level_4::getNextBlock() {
    if (rand) {
        std::vector<BlockShape> shapeWeightList = {BlockShape::I, // 1 I
                                                   BlockShape::J, // 1 J
                                                   BlockShape::L, // 1 L
                                                   BlockShape::O, // 1 O
                                                   BlockShape::S, // 2 S
                                                   BlockShape::S,
                                                   BlockShape::Z, // 2 Z
                                                   BlockShape::Z,
                                                   BlockShape::T}; // 1 T
        if (seed != -1) srand(seed);
        int idx = std::rand() % shapeWeightList.size();
        return shapeWeightList[idx];
    } else {
        return seq.get_next_block();
    }
}

void Level_4::noRandom(const std::string &file_name) {
    try {
        seq.set_sequence(file_name);
    } catch (EmptySequenceException &e) {
        std::cerr << "given sequence is invalid" << std::endl;
        return;
    }
    rand = false;
}

void Level_4::random() {
    rand = true;
}

void Level_4::action_left(Tetris *tetris) {
    try {
        tetris->get_current_block()->down(1);
    } catch (InvalidActionException &err) {
        std::cerr << err.what() << std::endl;
    }
}

void Level_4::action_right(Tetris *tetris) {
    try {
       tetris->get_current_block()->down(1);
    } catch (InvalidActionException &err) {
        std::cerr << err.what() << std::endl;
    }
}

void Level_4::action_down(Tetris *tetris) {
    try {
        tetris->get_current_block()->down(1);
    } catch (InvalidActionException &err) {
        std::cerr << err.what() << std::endl;
    }
}

void Level_4::action_drop(Tetris *tetris, int row_cleared) {
    if (row_cleared == 0) {
        if (++counter % 5 == 0) {
            tetris->placeTiny();
        }
    } else {
        counter = 0;
    }
}

void Level_4::action_clockwise(Tetris *tetris) {
    try {
        tetris->get_current_block()->down(1);
    } catch (InvalidActionException &err) {
        std::cerr << err.what() << std::endl;
    }
}

void Level_4::action_counter_clockwise(Tetris *tetris) {
    try {
        tetris->get_current_block()->down(1);
    } catch (InvalidActionException &err) {
        std::cerr << err.what() << std::endl;
    }
}



#if 0
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "blockShape.h"
#include "level_4.h"

Level_4::Level_4(std::string file, bool rand) :
Level{4, file, rand} {}

int Level_4::getTinyCounter() { return tiny_counter; }

BlockShape Level_4::getNextBlock() override {
int index = -1;
if (rand) {
blktype.clear();
blktype = {'S', 'Z', 'I', 'J', 'L', 'O', 'S', 'Z', 'T'};
int index = rand() % blktype.size();
} else {
readFile();
}

if (index != -1) counter = index;

int length = blkseq.size();
char target = blktype[counter++];
if (counter >= length) counter = 0;

++tiny_counter; /////////////////// maybe

BlockShapeUtil *util = new BlockShapeUtil{};
BlockShape ret;
try {
ret = util->to_block_shape(target);
}
catch (InvalidArgumentException &e) {
throw e;
}
// TODO: we want to deliver that this block needs to be heavy
return ret;
}
#endif