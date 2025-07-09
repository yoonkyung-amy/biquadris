// This is interface of Grid class
#ifndef __GRID_H__
#define __GRID_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "block.h"
#include <stdexcept>

/**
 * Grid class is responsible of positions of the blocks
 */
class Grid {
    // ===== FIELD ===== //
    // width and height stores the width and height of the grid respectively
    const int width, height;

    // board stores the pointer of blocks at given specific positions
    // NOTE:
    //    empty cell is represented as nullptr
    std::vector<std::vector<Block*>> board;

    // isFull(int row) check is the row is full of some block
    // REQUIRES:
    //    0 <= row < height  [NOT ASSERTED] // TODO: implement exception
    bool isFull(int row) const;

    // isEmpty(int row) check is the row is empty
    // REQUIRES:
    //    0 <= row < height  [NOT ASSERTED] // TODO: implement exception
    bool isEmpty(int row) const;

    // push(std::vector<Block*> &blocks, Block *block) adds the block if it's not repeated
    // NOTE:
    //    if block is nullptr, it automatically ignores and do nothing
    void push(std::vector<Block*> &blocks, Block *block);
public:
    // ===== CONSTRUCTOR ===== //
    // CONSTRUCTOR: Grid
    // REQUIRES:
    //    0 < width   [NOT ASSERTED]
    //    0 < height  [NOT ASSERTED]
    explicit Grid(int width, int height);

    // DESTRUCTOR: Grid
    // NOTE:
    //    empties the board to nullptr
    ~Grid();

    // ===== METHODS ===== //
    // getWidth() returns the width of the grid
    int getWidth() const noexcept;

    // getHeight() returns the height of the grid
    int getHeight() const noexcept;

    // getBoard(int row, int col) returns the block at (row,col)
    // REQUIRES:
    //    0 <= col < width
    //    0 <= row < height
    // NOTE:
    //    if row or col is out of boundary, throw invalid_argument Exception
    Block *getBoard(int row, int col) const;

    // setBoard(int row, int col, Block *block) set the (row,col) be block pointer
    // REQUIRES:
    //    0 <= col < width
    //    0 <= row < height
    // NOTE:
    //    if row or col is out of boundary, throw invalid_argument Exception
    void setBoard(int row, int col, Block *block);

    // dropped() removes any full rows and pull the rows above and modifies the
    //    block classes to synchronize with the new grid then return the number of rows removed
    int dropped();
};

#endif
