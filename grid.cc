// This is implementation of Grid class
#include "grid.h"

// CONSTRUCTOR: Grid
// REQUIRES:
//    0 < width   [NOT ASSERTED]
//    0 < height  [NOT ASSERTED]
Grid::Grid(int width, int height) : width{width}, height{height} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Grid Constructor" << std::endl;
#endif
    board.assign(height, std::vector<Block*>(width));
}

// DESTRUCTOR: Grid
// NOTE:
//    empties the board to nullptr
Grid::~Grid() {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Grid Destructor" << std::endl;
#endif
    for (auto &row : board) {
        for (auto &col : row) {
            col = nullptr;
        }
    }
}

bool Grid::isFull(int row) const {
    for (int col = 0; col < width; col++) {
        if (board[row][col] == nullptr) return false;
    }
    return true;
}

bool Grid::isEmpty(int row) const {
    for (int col = 0; col < width; col++) {
        if (board[row][col] != nullptr) return false;
    }
    return true;
}

void Grid::push(std::vector<Block *> &blocks, Block *block) {
    if (block == nullptr) return;
    bool isFound = false;
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i] == block) isFound = true;
    }
    if (!isFound) blocks.push_back(block);
}

int Grid::dropped() {
    std::vector<Block*> modified;
    std::vector<int> semi;
    int last_idx = -1;
    int row_cleared = 0;
    for (int row = 0; row < height; row++) {
        if (isFull(row)) {
            for (int col = 0; col < width; col++) {
                push(modified, board[row][col]);
                board[row][col] = nullptr;
            }
            last_idx = row;
            row_cleared++;
        }
    }
    if (last_idx < 0) return row_cleared;
    for (int row = 0; row < last_idx; row++) {
        if (!isFull(row) && !isEmpty(row)) semi.push_back(row);
    }
    for (int i = semi.size() - 1; i >= 0; i--) {
        if (semi[i] == last_idx) {
            last_idx--;
            continue;
        }
        board[semi[i]].swap(board[last_idx--]);
    }
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            push(modified, board[row][col]);
        }
    }
    for (int i = 0; i < modified.size(); i++) {
        modified[i]->syncToBoard();
    }
    return row_cleared;
}

// getWidth() returns the width of the grid
int Grid::getWidth() const noexcept {
    return width;
}

// getHeight() returns the height of the grid
int Grid::getHeight() const noexcept {
    return height;
}

// getBoard(int row, int col) returns the block at (row,col)
// REQUIRES:
//    0 <= col < width
//    0 <= row < height
// NOTE:
//    if row or col is out of boundary, throw invalid_argument Exception
Block *Grid::getBoard(int row, int col) const {
    if (row < 0 || row >= height || col < 0 || col >= width) throw std::invalid_argument{"invalid_argument: row or col is out of board size"};
    return board[row][col];
}

// setBoard(int row, int col, Block *block) set the (row,col) be block pointer
// REQUIRES:
//    0 <= col < width
//    0 <= row < height
// NOTE:
//    if row or col is out of boundary, throw invalid_argument Exception
void Grid::setBoard(int row, int col, Block *block) {
    if (row < 0 || row >= height || col < 0 || col >= width) throw std::invalid_argument{"invalid_argument: row or col is out of board size"};
    board[row][col] = block;
}