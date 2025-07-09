// This is interface of BlockShape enum class, BlockShapeUtil class, and InvalidSymbolicCharException class
#ifndef __BLOCK_SHAPE_H__
#define __BLOCK_SHAPE_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include <iostream>
#include <vector>

/**
 * BlockShape class contains enum values that represents the block shapes and are bind with symbolic
 *    characters
 * REQUIRES:
 *    Each symbolic characters must be defined and are unique [NOT ASSERTED]
 */
enum class BlockShape {
    I = 'I',
    J = 'J',
    L = 'L',
    O = 'O',
    S = 'S',
    Z = 'Z',
    T = 'T',
    TINY = '*'
};

// Pimpl idiom for BlockShapeUtil class
struct BlockShapeUtilImpl;

/**
 * BlockShapeUtil class supports utility features for BlockShape enum class
 * NOTE:
 *    addition of new shape of block requires modification on BlockShapeUtil() constructor
 */
class BlockShapeUtil {
    // ===== PIMPL IDIOM ===== //
    BlockShapeUtilImpl *impl;
public:
    // ===== CONSTRUCTOR ===== //
    // CONSTRUCTOR: BlockShapeUtil
    BlockShapeUtil();

    // DESTRUCTOR: BlockShapeUtil
    ~BlockShapeUtil();

    // COPY-CONSTRUCTOR: BlockShapeUtil
    BlockShapeUtil(const BlockShapeUtil &other);

    // COPY-ASSIGNMENT: BlockShapeUtil
    BlockShapeUtil &operator=(const BlockShapeUtil &other);

    // MOVE-CONSTRUCTOR: BlockShapeUtil
    BlockShapeUtil(BlockShapeUtil &&other);

    // MOVE-ASSIGNMENT: BlockShapeUtil
    BlockShapeUtil &operator=(BlockShapeUtil &&other);

    // ===== METHODS ===== //
    // getBlockList() returns the vector list of BlockShapes
    std::vector<BlockShape> getBlockList() const noexcept;

    // to_char(BlockShape block) returns the symbolic_char that corresponds to the given block
    char to_char(BlockShape block) const noexcept;

    // to_block_shape(char symbolic_char) returns the BlockShape that corresponds to the given symbolic_char
    // REQUIRES:
    //    symbolic_char must be found in BlockShape enum class bound with some BlockShape
    // NOTE:
    //    if no matching BlockShape found, it throws InvalidSymbolicCharException
    BlockShape to_block_shape(char symbolic_char) const;
};

/**
 * InvalidSymbolicCharException class is called upon the exception case where some method is called with
 *    invalid char input
 */
class InvalidSymbolicCharException {
    // ===== FIELD ===== //
    // invalid_char stores character that is not a valid char input
    char invalid_char;
public:
    // ===== CONSTRUCTOR ===== //
    // CONSTRUCTOR: InvalidSymbolicCharException
    InvalidSymbolicCharException(char invalid_char);

    // DESTRUCTOR: InvalidSymbolicCharException
    ~InvalidSymbolicCharException() = default;
    
    // ===== METHODS ===== //
    // getInvalidChar() returns the specific character that is not valid as a char input
    char getInvalidChar() const noexcept;

    // printException() prints the error message on standard error
    // NOTE:
    //    it follows that format: "Block shape that corresponds to `invalid_char` is not found."
    void printException() const;
};

#endif
