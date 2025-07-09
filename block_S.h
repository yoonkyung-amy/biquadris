#ifndef __BLOCK_S_H__
#define __BLOCK_S_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "block.h"

class Block_S : public Block {
public:
    explicit Block_S(Grid *board, int level, Color color = Color::Green);
    ~Block_S() {
#if DEBUG_LEVEL > 0
        #include <iostream>
    std::cout << "Block_S Destructor" << std::endl;
#endif
    }
};

#endif
