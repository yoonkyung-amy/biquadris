#ifndef __BLOCK_DISPENSER_TINY_H__
#define __BLOCK_DISPENSER_TINY_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "blockDispenser.h"
#include "block_tiny.h"

class BlockDispenser_tiny : public BlockDispenser {
public:
    explicit BlockDispenser_tiny(Grid *grid);
    ~BlockDispenser_tiny() {
#if DEBUG_LEVEL > 0
        #include <iostream>
    std::cout << "BlockDispenser_tiny Destructor" << std::endl;
#endif
    }
    Block *getBlock(int level) override;
};

#endif
