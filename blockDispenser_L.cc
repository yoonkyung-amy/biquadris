#include "blockDispenser_L.h"

BlockDispenser_L::BlockDispenser_L(Grid *grid) : BlockDispenser{grid} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "BlockDispenser_L Constructor" << std::endl;
#endif
}

Block *BlockDispenser_L::getBlock(int level) {
    return new Block_L{grid, level};
}
