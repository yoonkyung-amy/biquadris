#include "blockDispenser_O.h"

BlockDispenser_O::BlockDispenser_O(Grid *grid) : BlockDispenser{grid} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "BlockDispenser_O Constructor" << std::endl;
#endif
}

Block *BlockDispenser_O::getBlock(int level) {
    return new Block_O{grid, level};
}
