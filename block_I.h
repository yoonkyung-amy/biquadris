#ifndef __BLOCK_I_H__
#define __BLOCK_I_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "block.h"

class Block_I : public Block {
public:
    explicit Block_I(Grid *board, int level, Color color = Color::Cyan);
    ~Block_I() {
#if DEBUG_LEVEL > 0
        #include <iostream>
    std::cout << "Block_I Destructor" << std::endl;
#endif
    }
};

#endif
