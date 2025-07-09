#ifndef __BLOCK_DISPENSER_L_H__
#define __BLOCK_DISPENSER_L_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "blockDispenser.h"
#include "block_L.h"

class BlockDispenser_L : public BlockDispenser {
public:
    explicit BlockDispenser_L(Grid *grid);
    ~BlockDispenser_L() {
#if DEBUG_LEVEL > 0
        #include <iostream>
    std::cout << "BlockDispenser_L Destructor" << std::endl;
#endif
    }
    Block *getBlock(int level) override;
};

#endif
