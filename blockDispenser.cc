#include "blockDispenser.h"

BlockDispenser::BlockDispenser(Grid *grid) : grid{grid} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "BlockDispenser Constructor" << std::endl;
#endif
}

BlockDispenser::~BlockDispenser() {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "BlockDispenser Destructor" << std::endl;
#endif
}