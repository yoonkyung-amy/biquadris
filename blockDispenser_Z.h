#ifndef __BLOCK_DISPENSER_Z_H__
#define __BLOCK_DISPENSER_Z_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "blockDispenser.h"
#include "block_Z.h"

class BlockDispenser_Z : public BlockDispenser {
public:
    explicit BlockDispenser_Z(Grid *grid);
    ~BlockDispenser_Z() {
#if DEBUG_LEVEL > 0
        #include <iostream>
    std::cout << "BlockDispenser_Z Destructor" << std::endl;
#endif
    }
    Block *getBlock(int level) override;
};

#endif
