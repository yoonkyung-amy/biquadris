#ifndef __BLOCK_DISPENSER_O_H__
#define __BLOCK_DISPENSER_O_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "blockDispenser.h"
#include "block_O.h"

class BlockDispenser_O : public BlockDispenser {
public:
    explicit BlockDispenser_O(Grid *grid);
    ~BlockDispenser_O() {
#if DEBUG_LEVEL > 0
        #include <iostream>
    std::cout << "BlockDispenser_O Destructor" << std::endl;
#endif
    }
    Block *getBlock(int level) override;
};

#endif
