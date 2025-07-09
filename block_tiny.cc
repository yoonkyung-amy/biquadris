#include "block_tiny.h"

/**
 *   Diagram: '*'
 *   + - - - - +
 * 3 |         |
 * 2 |         |
 * 1 |         |
 * 0 | *       |
 *   + - - - - +
 *     0 1 2 3
 *
 *   coordinate system: (row, column)
 */
Block_tiny::Block_tiny(Grid *board, int level, Color color) : Block{board, BlockShape::TINY, color, level} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Block_tiny Constructor" << std::endl;
#endif
    addShape(std::make_pair(0, 0));
}
