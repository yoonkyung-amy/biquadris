#include "blockDispenser_J.h"

BlockDispenser_J::BlockDispenser_J(Grid *grid) : BlockDispenser{grid} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "BlockDispenser_J Constructor" << std::endl;
#endif
}

Block *BlockDispenser_J::getBlock(int level) {
    return new Block_J{grid, level};
}
