#include "block_O.h"

/**
 *   Diagram: 'O'
 *   + - - - - +
 * 3 |         |
 * 2 |         |
 * 1 | O O     |
 * 0 | O O     |
 *   + - - - - +
 *     0 1 2 3
 *
 *   coordinate system: (row, column)
 */
Block_O::Block_O(Grid *board, int level, Color color) : Block{board, BlockShape::O, color, level} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Block_O Constructor" << std::endl;
#endif
    addShape(std::make_pair(0, 0));
    addShape(std::make_pair(0, 1));
    addShape(std::make_pair(1, 0));
    addShape(std::make_pair(1, 1));
}
