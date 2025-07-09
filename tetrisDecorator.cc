#include "tetrisDecorator.h"

TetrisDecorator::TetrisDecorator(TetrisAbstract *component) : component{component} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Tetris Decorator Constructor" << std::endl;
#endif
}

TetrisDecorator::~TetrisDecorator() {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Tetris Decorator Destructor" << std::endl;
#endif
}