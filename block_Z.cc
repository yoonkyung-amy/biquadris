#include "block_Z.h"

/**
 *   Diagram: 'Z'
 *   + - - - - +
 * 3 |         |
 * 2 |         |
 * 1 | Z Z     |
 * 0 |   Z Z   |
 *   + - - - - +
 *     0 1 2 3
 *
 *   coordinate system: (row, column)
 */
Block_Z::Block_Z(Grid *board, int level, Color color) : Block{board, BlockShape::Z, color, level} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Block_Z Constructor" << std::endl;
#endif
    addShape(std::make_pair(0, 1));
    addShape(std::make_pair(0, 2));
    addShape(std::make_pair(1, 0));
    addShape(std::make_pair(1, 1));
}
