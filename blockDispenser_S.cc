#include "blockDispenser_S.h"

BlockDispenser_S::BlockDispenser_S(Grid *grid) : BlockDispenser{grid} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "BlockDispenser_S Constructor" << std::endl;
#endif
}

Block *BlockDispenser_S::getBlock(int level) {
    return new Block_S{grid, level};
}
