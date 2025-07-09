#include "blockDispenser_Z.h"

BlockDispenser_Z::BlockDispenser_Z(Grid *grid) : BlockDispenser{grid} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "BlockDispenser_Z Constructor" << std::endl;
#endif
}

Block *BlockDispenser_Z::getBlock(int level) {
    return new Block_Z{grid, level};
}
