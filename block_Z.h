#ifndef __BLOCK_Z_H__
#define __BLOCK_Z_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "block.h"

class Block_Z : public Block {
public:
    explicit Block_Z(Grid *board, int level, Color color = Color::Red);
    ~Block_Z() {
#if DEBUG_LEVEL > 0
        #include <iostream>
    std::cout << "Block_Z Destructor" << std::endl;
#endif
    }
};

#endif
