// This is interface of Block class
#ifndef __BLOCK_H__
#define __BLOCK_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "blockShape.h"
#include "Color.h"
#include <utility>
#include <vector>
#include <stdexcept>
#include <string>

/**
 * Grid class is forward declared to prevent circular dependency
 */
class Grid;

/**
 * Block class is responsible of the shape and location of the block and its movements
 * REQUIRES:
 *    board must not be nullptr [NOT ASSERTED]
 * NOTE:
 *    coordinate system of pivot is absolute position which origin is located at top-left corner as (0,0)
 *    coordinate system of shape is relative position which origin is located at bottom-left corner as (0,0) relative to pivot
 *    the movements made in Block automatically applies to the grid in board
 *    movements/modifications made outside of the Block must be updated to the blocks via SyncToBoard()
 */
class Block {
    // ===== FIELD ===== //
    // board stores the pointer back to the Grid it belong
    Grid *board;

    // type stores the type of the block
    BlockShape type;

    // color stores the color for the block
    Color color;

    // placed indicated if the block is ever placed to the grid
    bool placed;

    // level stores the past level of the game when this block was created
    int level;

    // pivot saves the pivot coordinate of the block
    // NOTE:
    //    this coordinate is 'absolute' to the grid in board it belong
    //    i.e. origin (0,0) is top-left corner of the grid
    std::pair<int,int> pivot;

    // shape stores the relative positions about the pivot
    // NOTE:
    //    this coordinate is 'relative' to the pivot
    //    i.e. origin (0,0) is bottom-left corner where pivot is located
    std::vector<std::pair<int,int>> shape;

    // ===== METHODS ===== //
    // checkBoundary(std::pair<int,int> sample_pivot, const std::vector<std::pair<int,int>> &sample_shape) checks if sample
    //    shape is within the boundary of the board
    // NOTE:
    //    if valid return true otherwise false
    bool checkBoundary(std::pair<int,int> sample_pivot, const std::vector<std::pair<int,int>> &sample_shape) const noexcept;

    // checkOverlap(std::pair<int,int> sample_pivot, const std::vector<std::pair<int,int>> &sample_shape) checks if sample
    //    shape overlaps with other block
    // NOTE:
    //    if valid return true otherwise false
    bool checkOverlap(std::pair<int,int> sample_pivot, const std::vector<std::pair<int,int>> &sample_shape) const noexcept;

    // removeFromBoard() removes the block from the board
    void removeFromBoard();

    // updateToBoard() updates the shape of the block to the board
    // REQUIRES:
    //    the shape must be within the boundary
    //    the shape must not overlap with any other blocks
    // NOTE:
    //    if shape is out of boundary and/or overlaps with other block, throw InvalidActionException
    void updateToBoard();
protected:
    // ===== METHODS ===== //
    // setShape(std::vector<std::pair<int,int>> shape) set the shape of the block
    void setShape(const std::vector<std::pair<int,int>> &new_shape);

    // addShape(std::pair<int,int> coordinate) add the coordinate to the shape
    void addShape(std::pair<int,int> coordinate);
public:
    // ===== CONSTRUCTORS ===== //
    // CONSTRUCTOR: Block
    // REQUIRES:
    //    board is not nullptr [NOT ASSERTED]
    Block(Grid *board, BlockShape type, Color color, int level);

    // DESTRUCTOR: Block
    // NOTE:
    //    DO NOT delete board
    virtual ~Block();

    // COPY-CONSTRUCTOR: Block
    // NOTE:
    //    DO shallow copy the board pointer
    Block(const Block &other);

    // COPY-ASSIGNMENT: Block
    // NOTE:
    //    DO shallow copy the board pointer
    Block &operator=(const Block &other);

    // MOVE-CONSTRUCTOR: Block
    Block(Block &&other);

    // MOVE-ASSIGNMENT: Block
    Block &operator=(Block &&other);

    // ===== METHODS ===== //
    // getType() returns the BlockShape of this block
    BlockShape getType() const noexcept;

    // getColor() returns the Color of this block
    Color getColor() const noexcept;

    // setColor(Color color) set the Color of this block
    void setColor(Color color) noexcept;

    // getLevel() returns the level stored in this block
    int getLevel() const noexcept;

    // getShape() returns the shape of the block
    std::vector<std::pair<int,int>> getShape() const noexcept;

    // placeAt(int row, int col) place the block to the grid
    // REQUIRES:
    //    shape is none-empty
    //    shape does not get out of boundary
    // NOTE:
    //    if shape is out of boundary or shape is empty vector, throw InvalidActionException
    //    turns placed to true and set the pivot
    //    if the shape of the block overlaps with other block, return true to indicate game over, otherwise false
    bool placeAt(int row, int col);

    // left(int step) moves the block leftward about step blocks
    // REQUIRES:
    //    0 <= step
    //    placed == true
    //    shape is none-empty
    // NOTE:
    //    if step is negative or block is not placed or shape is empty vector, throw InvalidActionException
    //    move pivot leftward at MAXIMUM, step blocks - if unable to move further, stop
    void left(int step);

    // right(int step) moves the block rightward about step blocks
    // REQUIRES:
    //    0 <= step
    //    placed == true
    //    shape is none-empty
    // NOTE:
    //    if step is negative or block is not placed or shape is empty vector, throw InvalidActionException
    //    move pivot rightward at MAXIMUM, step blocks - if unable to move further, stop
    void right(int step);

    // down(int step) moves the block downward about step blocks
    // REQUIRES:
    //    0 <= step
    //    placed == true
    //    shape is none-empty
    // NOTE:
    //    if step is negative or block is not placed or shape is empty vector, throw InvalidActionException
    //    move pivot downward at MAXIMUM, step blocks - if unable to move further, stop
    bool down(int step);

    // drop() drops the block bottom most location
    // REQUIRES:
    //    placed == true
    //    shape is none-empty
    // NOTE:
    //    if block is not placed or shape is empty vector, throw InvalidActionException
    //    drop the pivot bottom most position possible
    //    this method is functionally different compare to Tetris::drop()
    void drop();

    // clockwise(int step) rotates the block's shape clockwise
    // REQUIRES:
    //    0 <= step
    //    placed == true
    //    shape is none-empty
    // NOTE:
    //    if step is negative or block is not placed or shape is empty vector, throw InvalidActionException
    //    rotates the shape 90 degrees clockwise direction per step
    void clockwise(int step);

    // clockwise(int step) rotates the block's shape counter clockwise
    // REQUIRES:
    //    0 <= step
    //    placed == true
    //    shape is none-empty
    // NOTE:
    //    if step is negative or block is not placed or shape is empty vector, throw InvalidActionException
    //    rotates the shape 90 degrees counter clockwise direction per step
    void counter_clockwise(int step);

    // syncToBoard modifies the block's pivot and shape to match the board's current status
    // REQUIRES:
    //    placed == true
    // NOTE:
    //    if block is not placed to the board, throw InvalidActionException
    void syncToBoard();
};

/**
 * InvalidActionException class is being thrown when block's action is called in invalid conditions
 */
class InvalidActionException : public std::exception {
    // ===== FIELD ===== //
    // msg stores the error message
    const std::string msg;

public:
    // ===== CONSTRUCTOR ===== //
    // CONSTRUCTOR: InvalidActionException
    explicit InvalidActionException(const std::string &msg);

    // ===== METHODS ===== //
    // what() returns the error message stored
    const char *what() const noexcept override;
};

#endif
