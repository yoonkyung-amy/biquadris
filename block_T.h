#ifndef __BLOCK_T_H__
#define __BLOCK_T_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "block.h"

class Block_T : public Block {
public:
    explicit Block_T(Grid *board, int level, Color color = Color::Purple);
    ~Block_T() {
#if DEBUG_LEVEL > 0
        #include <iostream>
    std::cout << "Block_T Destructor" << std::endl;
#endif
    }
};

#endif
