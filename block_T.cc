#include "block_T.h"

/**
 *   Diagram: 'T'
 *   + - - - - +
 * 3 |         |
 * 2 |         |
 * 1 | T T T   |
 * 0 |   T     |
 *   + - - - - +
 *     0 1 2 3
 *
 *   coordinate system: (row, column)
 */
Block_T::Block_T(Grid *board, int level, Color color) : Block{board, BlockShape::T, color, level} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Block_T Constructor" << std::endl;
#endif
    addShape(std::make_pair(0, 1));
    addShape(std::make_pair(1, 0));
    addShape(std::make_pair(1, 1));
    addShape(std::make_pair(1, 2));
}
