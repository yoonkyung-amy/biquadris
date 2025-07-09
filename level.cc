#include "level.h"
#include "tetris.h"

Level::Level(std::string standard_sequence_file, bool rand, int seed) :
seq{standard_sequence_file},
rand{rand},
seed{seed} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Level Constructor" << std::endl;
#endif
}

Level::~Level() {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Level Destructor" << std::endl;
#endif
}

#if 0
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

#include "level.h"

Level::Level(int level, std::string file = "", bool rand = false)
        : level{level}, file{file}, rand{rand} {}

void Level::readFile() {
    blkseq.clear();
    char blk;
    std::ifstream seq(file);
    while (seq >> blk) {
        blkseq.push_back(blk);
    }
}

#endif