#ifndef __BLOCK_DISPENSER_I_H__
#define __BLOCK_DISPENSER_I_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "blockDispenser.h"
#include "block_I.h"

class BlockDispenser_I : public BlockDispenser {
public:
    explicit BlockDispenser_I(Grid *grid);
    ~BlockDispenser_I() {
#if DEBUG_LEVEL > 0
        #include <iostream>
    std::cout << "BlockDispenser_I Destructor" << std::endl;
#endif
    }
    Block *getBlock(int level) override;
};

#endif
