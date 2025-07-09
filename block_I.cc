#include "block_I.h"

/**
 *   Diagram: 'I'
 *   + - - - - +
 * 3 |         |
 * 2 |         |
 * 1 |         |
 * 0 | I I I I |
 *   + - - - - +
 *     0 1 2 3
 *
 *   coordinate system: (row, column)
 */
Block_I::Block_I(Grid *board, int level, Color color) : Block{board, BlockShape::I, color, level} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Block_I Constructor" << std::endl;
#endif
    addShape(std::make_pair(0, 0));
    addShape(std::make_pair(0, 1));
    addShape(std::make_pair(0, 2));
    addShape(std::make_pair(0, 3));
}
