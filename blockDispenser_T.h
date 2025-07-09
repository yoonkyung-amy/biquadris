#ifndef __BLOCK_DISPENSER_T_H__
#define __BLOCK_DISPENSER_T_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "blockDispenser.h"
#include "block_T.h"

class BlockDispenser_T : public BlockDispenser {
public:
    explicit BlockDispenser_T(Grid *grid);
    ~BlockDispenser_T() {
#if DEBUG_LEVEL > 0
        #include <iostream>
    std::cout << "BlockDispenser_T Destructor" << std::endl;
#endif
    }
    Block *getBlock(int level) override;
};

#endif
