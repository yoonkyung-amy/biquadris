#include "blockDispenser_tiny.h"

BlockDispenser_tiny::BlockDispenser_tiny(Grid *grid) : BlockDispenser{grid} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "BlockDispenser_tiny Constructor" << std::endl;
#endif
}

Block *BlockDispenser_tiny::getBlock(int level) {
    return new Block_tiny{grid, level};
}
