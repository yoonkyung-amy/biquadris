#include "block_S.h"

/**
 *   Diagram: 'S'
 *   + - - - - +
 * 3 |         |
 * 2 |         |
 * 1 |   S S   |
 * 0 | S S     |
 *   + - - - - +
 *     0 1 2 3
 *
 *   coordinate system: (row, column)
 */
Block_S::Block_S(Grid *board, int level, Color color) : Block{board, BlockShape::S, color, level} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Block_S Constructor" << std::endl;
#endif
    addShape(std::make_pair(0, 0));
    addShape(std::make_pair(0, 1));
    addShape(std::make_pair(1, 1));
    addShape(std::make_pair(1, 2));
}
