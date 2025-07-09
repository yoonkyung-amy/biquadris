#ifndef __BLOCK_L_H__
#define __BLOCK_L_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "block.h"

class Block_L : public Block {
public:
    explicit Block_L(Grid *board, int level, Color color = Color::Orange);
    ~Block_L() {
#if DEBUG_LEVEL > 0
        #include <iostream>
    std::cout << "Block_L Destructor" << std::endl;
#endif
    }
};

#endif
