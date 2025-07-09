#ifndef __BLOCK_DISPENSER_S_H__
#define __BLOCK_DISPENSER_S_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "blockDispenser.h"
#include "block_S.h"

class BlockDispenser_S : public BlockDispenser {
public:
    explicit BlockDispenser_S(Grid *grid);
    ~BlockDispenser_S() {
#if DEBUG_LEVEL > 0
        #include <iostream>
    std::cout << "BlockDispenser_S Destructor" << std::endl;
#endif
    }
    Block *getBlock(int level) override;
};

#endif
