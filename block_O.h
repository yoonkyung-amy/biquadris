#ifndef __BLOCK_O_H__
#define __BLOCK_O_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "block.h"

class Block_O : public Block {
public:
    explicit Block_O(Grid *board, int level, Color color = Color::Yellow);
    ~Block_O() {
#if DEBUG_LEVEL > 0
        #include <iostream>
    std::cout << "Block_O Destructor" << std::endl;
#endif
    }
};

#endif
