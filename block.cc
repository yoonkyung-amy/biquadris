// This is implementation of Block class
#include "block.h"
#include "grid.h"

// CONSTRUCTOR: Block
// REQUIRES:
//    board is not nullptr [NOT ASSERTED]
Block::Block(Grid *board, BlockShape type, Color color, int level) :
board{board},
type{type},
color{color},
placed{false},
level{level} {
#if DEBUG_LEVEL > 0
#include <iostream>
    std::cout << "Block Constructor" << std::endl;
#endif
}

// DESTRUCTOR: Block
// NOTE:
//    DO NOT delete board
Block::~Block() {
	board = nullptr;
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Block Destructor" << std::endl;
#endif
}

// COPY-CONSTRUCTOR: Block
// NOTE:
//    DO shallow copy the board pointer
Block::Block(const Block &other) :
board{other.board},
type{other.type},
color{other.color},
placed{other.placed},
pivot{other.pivot},
shape{other.shape} {}

// COPY-ASSIGNMENT: Block
// NOTE:
//    DO shallow copy the board pointer
Block &Block::operator=(const Block &other) {
    Block temp{other};
    std::swap(board, temp.board);
    std::swap(type, temp.type);
    std::swap(color, temp.color);
    std::swap(placed, temp.placed);
    std::swap(pivot, temp.pivot);
    std::swap(shape, temp.shape);
    return *this;
}

// MOVE-CONSTRUCTOR: Block
Block::Block(Block &&other) :
board{other.board},
type{other.type},
color{other.color},
placed{other.placed},
pivot{other.pivot},
shape{other.shape} {
    other.board = nullptr;
}

// MOVE-ASSIGNMENT: Block
Block &Block::operator=(Block &&other) {
    std::swap(board, other.board);
    std::swap(type, other.type);
    std::swap(color, other.color);
    std::swap(placed, other.placed);
    std::swap(pivot, other.pivot);
    std::swap(shape, other.shape);
    return *this;
}

// checkBoundary(std::pair<int,int> sample_pivot, const std::vector<std::pair<int,int>> &sample_shape) checks if sample
//    shape is within the boundary of the board
// NOTE:
//    if valid return true otherwise false
bool Block::checkBoundary(std::pair<int, int> sample_pivot,
                          const std::vector<std::pair<int, int>> &sample_shape) const noexcept {
    for (auto &i : sample_shape) {
        if (sample_pivot.first - i.first < 0 ||
            sample_pivot.first - i.first >= board->getHeight() ||
            sample_pivot.second + i.second < 0 ||
            sample_pivot.second + i.second >= board->getWidth()) {
            return false;
        }
    }
    return true;
}

// checkOverlap(std::pair<int,int> sample_pivot, const std::vector<std::pair<int,int>> &sample_shape) checks if sample
//    shape overlaps with other block
// NOTE:
//    if valid return true otherwise false
bool Block::checkOverlap(std::pair<int, int> sample_pivot,
                         const std::vector<std::pair<int, int>> &sample_shape) const noexcept {
    for (auto &i : sample_shape) {
        if (board->getBoard(sample_pivot.first - i.first,
                            sample_pivot.second + i.second) != nullptr &&
            board->getBoard(sample_pivot.first - i.first,
                            sample_pivot.second + i.second) != this) {
            return false;
        }
    }
    return true;
}

// removeFromBoard() removes the block from the board
void Block::removeFromBoard() {
    for (int row = 0; row < board->getHeight(); row++) {
        for (int col = 0; col < board->getWidth(); col++) {
            if (board->getBoard(row, col) == this) board->setBoard(row, col, nullptr);
        }
    }
}

// updateToBoard() updates the shape of the block to the board
// REQUIRES:
//    the shape must be within the boundary
//    the shape must not overlap with any other blocks
// NOTE:
//    if shape is out of boundary and/or overlaps with other block, throw InvalidActionException
void Block::updateToBoard() {
    if (!checkBoundary(pivot, shape)) throw InvalidActionException{"UpdateToBoard: block is out of boundary"};
    if (!checkOverlap(pivot, shape)) throw InvalidActionException{"UpdateToBoard: block overlaps with other block"};
    for (auto &i : shape) {
        board->setBoard(pivot.first - i.first, pivot.second + i.second, this);
    }
}

// setShape(const std::vector<std::pair<int,int>> &new_shape) set the shape of the block
void Block::setShape(const std::vector<std::pair<int,int>> &new_shape) {
    std::vector<std::pair<int,int>> temp{new_shape};
    shape.swap(temp);
}

// addShape(std::pair<int,int> coordinate) add the coordinate to the shape
void Block::addShape(std::pair<int,int> coordinate) {
    shape.emplace_back(coordinate.first, coordinate.second);
}

// getType() returns the BlockShape of this block
BlockShape Block::getType() const noexcept {
    return type;
}

// getColor() returns the Color of this block
Color Block::getColor() const noexcept {
    return color;
}

// setColor(Color color) set the Color of this block
void Block::setColor(Color new_color) noexcept {
    color = new_color;
}

// getLevel() returns the level stored in this block
int Block::getLevel() const noexcept {
    return level;
}

// getShape() returns the shape of the block
std::vector<std::pair<int, int>> Block::getShape() const noexcept {
    return shape;
}

// placeAt(int row, int col) place the block to the grid
// REQUIRES:
//    shape is none-empty
//    shape does not get out of boundary
// NOTE:
//    if shape is out of boundary or shape is empty vector, throw InvalidActionException
//    turns placed to true and set the pivot
//    if the shape of the block overlaps with other block, return true to indicate game over, otherwise false
bool Block::placeAt(int row, int col) {
    // check if shape is empty
    if (shape.empty()) throw InvalidActionException{"placeAt: shape is not set"};
    // create a sample pivot
    std::pair<int,int> sample_pivot = std::make_pair(row,col);
    // check if shape is out of boundary
    if (!checkBoundary(sample_pivot, shape)) throw InvalidActionException{"placeAt: block is out of boundary"};
    // check if shape overlaps with other block
    if (!checkOverlap(sample_pivot, shape)) return true;
    // set pivot
    pivot = sample_pivot;
    // turn placed true
    placed = true;
    // remove existing blocks (if applicable)
    removeFromBoard();
    // update the new coordinate to the grid
    updateToBoard();
    // return false by default
    return false;
}

// left(int step) moves the block leftward about step blocks
// REQUIRES:
//    0 <= step
//    placed == true
//    shape is none-empty
// NOTE:
//    if step is negative or block is not placed or shape is empty vector, throw InvalidActionException
//    move pivot leftward at MAXIMUM, step blocks - if unable to move further, stop
void Block::left(int step) {
    // check requirements
    if (step < 0) throw InvalidActionException{"left: multiplicities must be non-negative"};
    if (!placed) throw InvalidActionException{"left: block must be placed to the grid"};
    if (shape.empty()) throw InvalidActionException{"left: shape is not set"};
    // create sample pivot
    std::pair<int,int> sample_pivot = std::make_pair(pivot.first, pivot.second);
    for (int counter = 0; counter < step; counter++) {
        // translate sample pivot
        sample_pivot.second -= 1;
        // check if new pivot is valid action, if not, restore the previous state and break
        if (!checkBoundary(sample_pivot, shape) || !checkOverlap(sample_pivot, shape)) {
            sample_pivot.second += 1;
            break;
        }
    }
    // update the pivot
    pivot = sample_pivot;
    // remove existing blocks
    removeFromBoard();
    // update the board
    try {
        updateToBoard();
    } catch (InvalidActionException &err) {
        // this line of code shouldn't be reached
        std::cerr << "left: FATAL ERROR" << std::endl;
    }

}

// right(int step) moves the block rightward about step blocks
// REQUIRES:
//    0 <= step
//    placed == true
//    shape is none-empty
// NOTE:
//    if step is negative or block is not placed or shape is empty vector, throw InvalidActionException
//    move pivot rightward at MAXIMUM, step blocks - if unable to move further, stop
void Block::right(int step) {
    // check requirements
    if (step < 0) throw InvalidActionException{"right: multiplicities must be non-negative"};
    if (!placed) throw InvalidActionException{"right: block must be placed to the grid"};
    if (shape.empty()) throw InvalidActionException{"right: shape is not set"};
    // create sample pivot
    std::pair<int,int> sample_pivot = std::make_pair(pivot.first, pivot.second);
    for (int counter = 0; counter < step; counter++) {
        // translate sample pivot
        sample_pivot.second += 1;
        // check if new pivot is valid action, if not, restore the previous state and break
        if (!checkBoundary(sample_pivot, shape) || !checkOverlap(sample_pivot, shape)) {
            sample_pivot.second -= 1;
            break;
        }
    }
    // update the pivot
    pivot = sample_pivot;
    // remove existing blocks
    removeFromBoard();
    // update the board
    try {
        updateToBoard();
    } catch (InvalidActionException &err) {
        // this line of code shouldn't be reached
        std::cerr << "right: FATAL ERROR" << std::endl;
    }
}

// down(int step) moves the block downward about step blocks
// REQUIRES:
//    0 <= step
//    placed == true
//    shape is none-empty
// NOTE:
//    if step is negative or block is not placed or shape is empty vector, throw InvalidActionException
//    move pivot downward at MAXIMUM, step blocks - if unable to move further, stop
bool Block::down(int step) {
    // check requirements
    if (step < 0) throw InvalidActionException{"down: multiplicities must be non-negative"};
    if (!placed) throw InvalidActionException{"down: block must be placed to the grid"};
    if (shape.empty()) throw InvalidActionException{"down: shape is not set"};
    // create sample pivot
    bool moved = true;
    std::pair<int,int> sample_pivot = std::make_pair(pivot.first, pivot.second);
    for (int counter = 0; counter < step; counter++) {
        // translate sample pivot
        sample_pivot.first += 1;
        // check if new pivot is valid action, if not, restore the previous state and break
        if (!checkBoundary(sample_pivot, shape) || !checkOverlap(sample_pivot, shape)) {
            sample_pivot.first -= 1;
            break;
        }
    }
    if (pivot == sample_pivot) moved = false;
    // update the pivot
    pivot = sample_pivot;
    // remove existing blocks
    removeFromBoard();
    // update the board
    try {
        updateToBoard();
    } catch (InvalidActionException &err) {
        // this line of code shouldn't be reached
        std::cerr << "down: FATAL ERROR" << std::endl;
    }
    return moved;
}

// drop() drops the block bottom most location
// REQUIRES:
//    placed == true
//    shape is none-empty
// NOTE:
//    if block is not placed or shape is empty vector, throw InvalidActionException
//    drop the pivot bottom most position possible
//    this method is functionally different compare to Tetris::drop()
void Block::drop() {
    // check requirements
    if (!placed) throw InvalidActionException{"drop: block must be placed to the grid"};
    if (shape.empty()) throw InvalidActionException{"drop: shape is not set"};
    // create sample pivot
    std::pair<int,int> sample_pivot = std::make_pair(pivot.first, pivot.second);
    while (true) {
        // translate sample pivot
        sample_pivot.first += 1;
        // check if new pivot is valid action, if not, restore the previous state and break
        if (!checkBoundary(sample_pivot, shape) || !checkOverlap(sample_pivot, shape)) {
            sample_pivot.first -= 1;
            break;
        }
    }
    // update the pivot
    pivot = sample_pivot;
    // remove existing blocks
    removeFromBoard();
    // update the board
    try {
        updateToBoard();
    } catch (InvalidActionException &err) {
        // this line of code shouldn't be reached
        std::cerr << "drop: FATAL ERROR" << std::endl;
    }
}

// clockwise(int step) rotates the block's shape clockwise
// REQUIRES:
//    0 <= step
//    placed == true
//    shape is none-empty
// NOTE:
//    if step is negative or block is not placed or shape is empty vector, throw InvalidActionException
//    rotates the shape 90 degrees clockwise direction per step
void Block::clockwise(int step) {
    // check requirements
    if (step < 0) throw InvalidActionException{"clockwise: multiplicities must be non-negative"};
    if (!placed) throw InvalidActionException{"clockwise: block must be placed to the grid"};
    if (shape.empty()) throw InvalidActionException{"clockwise: shape is not set"};
    // create sample shape
    std::vector<std::pair<int,int>> sample_shape{shape};
    for (int counter = 0; counter < step; counter++) {
        // create rotational_pivot which is minimum x and y from shape
        std::pair<int,int> rotational_pivot = sample_shape[0];
        for (auto &i : sample_shape) {
            if (i.first < rotational_pivot.first) rotational_pivot.first = i.first;
            if (i.second < rotational_pivot.second) rotational_pivot.second = i.second;
        }
        // create temp sample shape
        std::vector<std::pair<int,int>> temp_shape{sample_shape};
        // apply rotational matrix to the temporary shape
        for (int i = 0; i < sample_shape.size(); i++) {
            temp_shape[i] = std::make_pair(-1 * sample_shape[i].second, sample_shape[i].first);
        }
        // find minimum x and y of the temporary shape
        std::pair<int,int> min = temp_shape[0];
        for (auto &i : temp_shape) {
            if (i.first < min.first) min.first = i.first;
            if (i.second < min.second) min.second = i.second;
        }
        // translate the temporary shape
        for (auto &i : temp_shape) {
            i.first += (rotational_pivot.first - min.first);
            i.second += (rotational_pivot.second - min.second);
        }
        // check if temporary shape is valid
        if (!checkBoundary(pivot, temp_shape) || !checkOverlap(pivot, temp_shape)) {
            // do not save the temp shape and just break the loop here
            break;
        }
        // save the new shape as sample shape
        sample_shape.swap(temp_shape);
    }
    // update the shape
    shape.swap(sample_shape);
    // remove existing blocks
    removeFromBoard();
    // update the board
    try {
        updateToBoard();
    } catch (InvalidActionException &err) {
        // this line of code shouldn't be reached
        std::cerr << "clockwise: FATAL ERROR" << std::endl;
    }
}

// clockwise(int step) rotates the block's shape counter clockwise
// REQUIRES:
//    0 <= step
//    placed == true
//    shape is none-empty
// NOTE:
//    if step is negative or block is not placed or shape is empty vector, throw InvalidActionException
//    rotates the shape 90 degrees counter clockwise direction per step
void Block::counter_clockwise(int step) {
    // check requirements
    if (step < 0) throw InvalidActionException{"counter_clockwise: multiplicities must be non-negative"};
    if (!placed) throw InvalidActionException{"counter_clockwise: block must be placed to the grid"};
    if (shape.empty()) throw InvalidActionException{"counter_clockwise: shape is not set"};
    // create sample shape
    std::vector<std::pair<int,int>> sample_shape{shape};
    for (int counter = 0; counter < step; counter++) {
        // create rotational_pivot which is minimum x and y from shape
        std::pair<int,int> rotational_pivot = sample_shape[0];
        for (auto &i : sample_shape) {
            if (i.first < rotational_pivot.first) rotational_pivot.first = i.first;
            if (i.second < rotational_pivot.second) rotational_pivot.second = i.second;
        }
        // create temp sample shape
        std::vector<std::pair<int,int>> temp_shape{sample_shape};
        // apply rotational matrix to the temporary shape
        for (int i = 0; i < sample_shape.size(); i++) {
            temp_shape[i] = std::make_pair(sample_shape[i].second, -1 * sample_shape[i].first);
        }
        // find minimum x and y of the temporary shape
        std::pair<int,int> min = temp_shape[0];
        for (auto &i : temp_shape) {
            if (i.first < min.first) min.first = i.first;
            if (i.second < min.second) min.second = i.second;
        }
        // translate the temporary shape
        for (auto &i : temp_shape) {
            i.first += (rotational_pivot.first - min.first);
            i.second += (rotational_pivot.second - min.second);
        }
        // check if temporary shape is valid
        if (!checkBoundary(pivot, temp_shape) || !checkOverlap(pivot, temp_shape)) {
            // do not save the temp shape and just break the loop here
            break;
        }
        // save the new shape as sample shape
        sample_shape.swap(temp_shape);
    }
    // update the shape
    shape.swap(sample_shape);
    // remove existing blocks
    removeFromBoard();
    // update the board
    try {
        updateToBoard();
    } catch (InvalidActionException &err) {
        // this line of code shouldn't be reached
        std::cerr << "counter_clockwise: FATAL ERROR" << std::endl;
    }
}

// syncToBoard modifies the block's pivot and shape to match the board's current status
// REQUIRES:
//    placed == true
// NOTE:
//    if block is not placed to the board, throw InvalidActionException
void Block::syncToBoard() {
    // check requirements
    if (!placed) throw InvalidActionException{"syncToBoard: block must be placed to the grid"};
    // create sample pivot
    std::pair<int,int> sample_pivot;
    // create coordinate vector
    std::vector<std::pair<int,int>> coordinates;
    // find all coordinate of this blocks from the board
    for (int row = 0; row < board->getHeight(); row++) {
        for (int col = 0; col < board->getWidth(); col++) {
            if (board->getBoard(row,col) == this) {
                coordinates.emplace_back(row, col);
            }
        }
    }
    // if coordinate is empty, empty the shape and return
    if (coordinates.empty()) {
        shape.clear();
        return;
    }
    // set sample pivot to the bottom-left corner of the coordinates found
    sample_pivot = coordinates[0];
    for (int i = 0; i < coordinates.size(); i++) {
        if (coordinates[i].first < sample_pivot.first) sample_pivot.first = coordinates[i].first;
        if (coordinates[i].second < sample_pivot.second) sample_pivot.second = coordinates[i].second;
    }
    // create sample shape
    std::vector<std::pair<int,int>> sample_shape;
    // register new shape using the formula
    for (int i = 0; i < coordinates.size(); i++) {
        sample_shape.emplace_back(sample_pivot.first - coordinates[i].first,
                                  coordinates[i].second - sample_pivot.second);
    }
    // update the pivot and shape
    pivot = sample_pivot;
    shape.swap(sample_shape);
}

InvalidActionException::InvalidActionException(const std::string &msg) :
msg{"InvalidActionException: "+msg} {}

const char * InvalidActionException::what() const noexcept {
    return &msg[0];
}
