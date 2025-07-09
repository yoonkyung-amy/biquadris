#ifndef __BLOCK_TINY_H__
#define __BLOCK_TINY_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "block.h"

class Block_tiny : public Block {
public:
    explicit Block_tiny(Grid *board, int level, Color color = Color::Brown);
    ~Block_tiny() {
#if DEBUG_LEVEL > 0
        #include <iostream>
    std::cout << "Block_tiny Destructor" << std::endl;
#endif
    }
};

#endif
