#include "block_J.h"

/**
 *   Diagram: 'J'
 *   + - - - - +
 * 3 |         |
 * 2 |         |
 * 1 | J       |
 * 0 | J J J   |
 *   + - - - - +
 *     0 1 2 3
 *
 *   coordinate system: (row, column)
 */
Block_J::Block_J(Grid *board, int level, Color color) : Block{board, BlockShape::J, color, level} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Block_J Constructor" << std::endl;
#endif
    addShape(std::make_pair(0, 0));
    addShape(std::make_pair(0, 1));
    addShape(std::make_pair(0, 2));
    addShape(std::make_pair(1, 0));
}