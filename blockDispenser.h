#ifndef __BLOCK_DISPENSER_H__
#define __BLOCK_DISPENSER_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "block.h"

class BlockDispenser {
protected:
    Grid *grid;
public:
    explicit BlockDispenser(Grid *grid);
    virtual ~BlockDispenser();
    virtual Block *getBlock(int level) = 0;
};

#endif
