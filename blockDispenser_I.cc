#include "blockDispenser_I.h"

BlockDispenser_I::BlockDispenser_I(Grid *grid) : BlockDispenser{grid} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "BlockDispenser_I Constructor" << std::endl;
#endif
}

Block *BlockDispenser_I::getBlock(int level) {
    return new Block_I{grid, level};
}
