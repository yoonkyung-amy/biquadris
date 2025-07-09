#include "level_2.h"
#include "blockShape.h"
#include <vector>
#include <cstdlib>

Level_2::Level_2(const std::string &standard_sequence_file, int seed) :
        Level{standard_sequence_file, true, seed} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Level_2 Constructor" << std::endl;
#endif
}

BlockShape Level_2::getNextBlock() {
    std::vector<BlockShape> shapeWeightList = {BlockShape::I, // 1 I
                                               BlockShape::J, // 1 J
                                               BlockShape::L, // 1 L
                                               BlockShape::O, // 1 O
                                               BlockShape::S, // 1 S
                                               BlockShape::Z, // 1 Z
                                               BlockShape::T}; // 1 T
    if (seed != -1) srand(seed);
    int idx = std::rand() % shapeWeightList.size();
    return shapeWeightList[idx];
}

void Level_2::noRandom(const std::string &file_name) {} // no nothing

void Level_2::random() {} // no nothing

void Level_2::action_left(Tetris *tetris) {} // DO nothing by default

void Level_2::action_right(Tetris *tetris) {} // DO nothing by default

void Level_2::action_down(Tetris *tetris) {} // DO nothing by default

void Level_2::action_drop(Tetris *tetris, int row_cleared) {} // DO nothing by default

void Level_2::action_clockwise(Tetris *tetris) {} // DO nothing by default

void Level_2::action_counter_clockwise(Tetris *tetris) {} // DO nothing by default



#if 0
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "blockShape.h"
#include "level_2.h"

Level_2::Level_2(std::string file, bool rand) :
        Level{2, file, rand} {}

BlockShape Level_2::getNextBlock() override {
    int index = -1;
if (rand) {
blktype.clear();
blktype = {'I', 'J', 'L', 'O', 'S', 'Z', 'T'};
int index = rand() % blktype.size();
} else {
readFile();
}

if (index != -1) counter = index;

int length = blkseq.size();
char target = blktype[counter++];
if (counter >= length) counter = 0;

BlockShapeUtil *util = new BlockShapeUtil{};
BlockShape ret;
try {
ret = util->to_block_shape(target);
}
catch (InvalidArgumentException &e) {
throw e;
}

return ret;
}
#endif