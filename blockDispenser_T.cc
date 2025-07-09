#include "blockDispenser_T.h"

BlockDispenser_T::BlockDispenser_T(Grid *grid) : BlockDispenser{grid} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "BlockDispenser_T Constructor" << std::endl;
#endif
}

Block *BlockDispenser_T::getBlock(int level) {
    return new Block_T{grid, level};
}
