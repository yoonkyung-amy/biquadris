#ifndef __BLOCK_DISPENSER_J_H__
#define __BLOCK_DISPENSER_J_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "blockDispenser.h"
#include "block_J.h"

class BlockDispenser_J : public BlockDispenser {
public:
    explicit BlockDispenser_J(Grid *grid);
    ~BlockDispenser_J() {
#if DEBUG_LEVEL > 0
        #include <iostream>
    std::cout << "BlockDispenser_J Destructor" << std::endl;
#endif
    }
    Block *getBlock(int level) override;
};

#endif
