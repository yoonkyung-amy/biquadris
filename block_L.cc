#include "block_L.h"

/**
 *   Diagram: 'L'
 *   + - - - - +
 * 3 |         |
 * 2 |         |
 * 1 |     L   |
 * 0 | L L L   |
 *   + - - - - +
 *     0 1 2 3
 *
 *   coordinate system: (row, column)
 */
Block_L::Block_L(Grid *board, int level, Color color) : Block{board, BlockShape::L, color, level} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Block_L Constructor" << std::endl;
#endif
    addShape(std::make_pair(0, 0));
    addShape(std::make_pair(0, 1));
    addShape(std::make_pair(0, 2));
    addShape(std::make_pair(1, 2));
}
