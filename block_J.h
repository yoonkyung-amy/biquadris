#ifndef __BLOCK_J_H__
#define __BLOCK_J_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "block.h"

class Block_J : public Block {
public:
    explicit Block_J(Grid *board, int level, Color color = Color::Blue);
    ~Block_J() {
#if DEBUG_LEVEL > 0
        #include <iostream>
    std::cout << "Block_J Destructor" << std::endl;
#endif
    }
};

#endif
