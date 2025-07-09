// This is implementation of BlockShapeUtil class and InvalidSymbolicCharException class

#include "blockShape.h"
#include <utility>

// Pimpl idiom for BlockShapeUtil class
struct BlockShapeUtilImpl {
    std::vector<BlockShape> list;

    // ===== CONSTRUCTOR ===== //
    // CONSTRUCTOR: BlockShapeUtilImpl
    BlockShapeUtilImpl() = default;

    // DESTRUCTOR: BlockShapeUtilImpl
    ~BlockShapeUtilImpl() = default;

    // COPY-CONSTRUCTOR: BlockShapeUtilImpl
    BlockShapeUtilImpl(const BlockShapeUtilImpl &other);

    // COPY-ASSIGNMENT: BlockShapeUtilImpl
    BlockShapeUtilImpl &operator=(const BlockShapeUtilImpl &other);
};

// COPY-CONSTRUCTOR: BlockShapeUtilImpl
BlockShapeUtilImpl::BlockShapeUtilImpl(const BlockShapeUtilImpl &other) : list{other.list} {}

// COPY-ASSIGNMENT: BlockShapeUtilImpl
BlockShapeUtilImpl &BlockShapeUtilImpl::operator=(const BlockShapeUtilImpl &other) {
    BlockShapeUtilImpl temp{other};
    list.swap(temp.list);
    return *this;
}

// CONSTRUCTOR: BlockShapeUtil
// NOTE: addition of new shape of block requires modification on this constructor
BlockShapeUtil::BlockShapeUtil() : impl{new BlockShapeUtilImpl} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "BlockShapeUtil Constructor" << std::endl;
#endif
    impl->list.push_back(BlockShape::I);
    impl->list.push_back(BlockShape::J);
    impl->list.push_back(BlockShape::L);
    impl->list.push_back(BlockShape::O);
    impl->list.push_back(BlockShape::S);
    impl->list.push_back(BlockShape::Z);
    impl->list.push_back(BlockShape::T);
    impl->list.push_back(BlockShape::TINY);
    // push more BlockShapes below in case of addition of new blocks
}

// DESTRUCTOR: BlockShapeUtil
// NOTE: delete the pimpl idiom
BlockShapeUtil::~BlockShapeUtil() {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "BlockShape Destructor" << std::endl;
#endif
    delete impl;
}

// COPY-CONSTRUCTOR: BlockShapeUtil
BlockShapeUtil::BlockShapeUtil(const BlockShapeUtil &other) : impl{new BlockShapeUtilImpl} {
    impl->list = other.impl->list;
}

// COPY-ASSIGNMENT: BlockShapeUtil
// NOTE: Uses copy-and-swap idiom
BlockShapeUtil &BlockShapeUtil::operator=(const BlockShapeUtil &other) {
    BlockShapeUtil temp{other};
    std::swap(impl, temp.impl);
    return *this;
}

// MOVE-CONSTRUCTOR: BlockShapeUtil
BlockShapeUtil::BlockShapeUtil(BlockShapeUtil &&other) : impl{other.impl} {
    other.impl = nullptr;
}

// MOVE-ASSIGNMENT: BlockShapeUtil
BlockShapeUtil &BlockShapeUtil::operator=(BlockShapeUtil &&other) {
    std::swap(impl, other.impl);
    return *this;
}

// getBlockList() returns the vector list of BlockShapes
std::vector<BlockShape> BlockShapeUtil::getBlockList() const noexcept {
    return impl->list;
}

// to_char(BlockShape block) returns the symbolic_char that corresponds to the given block
char BlockShapeUtil::to_char(BlockShape block) const noexcept {
    return static_cast<char>(block);
}

// to_block_shape(char symbolic_char) returns the BlockShape that corresponds to the given symbolic_char
// REQUIRES:
//    symbolic_char must be found in BlockShape enum class bound with some BlockShape
// NOTE:
//    if no matching BlockShape found, it throws InvalidSymbolicCharException
BlockShape BlockShapeUtil::to_block_shape(char symbolic_char) const {
    char temp;
    int idx = -1;
    for (std::size_t i = 0; i < impl->list.size(); i++) {
        temp = static_cast<char>(impl->list[i]);
        if (symbolic_char == temp) {
            idx = i;
            break;
        }
    }
    if (idx == -1) throw InvalidSymbolicCharException{symbolic_char};
    return impl->list[idx];
}

// CONSTRUCTOR: InvalidSymbolicCharException
InvalidSymbolicCharException::InvalidSymbolicCharException(char invalid_char) :
invalid_char{invalid_char} {}

// getInvalidChar() returns the specific character that is not valid as a char input
char InvalidSymbolicCharException::getInvalidChar() const noexcept {
    return invalid_char;
}

// printException() prints the error message on standard error
// NOTE:
//    it follows that format: "Block shape that corresponds to `invalid_char` is not found."
void InvalidSymbolicCharException::printException() const {
    std::cerr << "Block shape that corresponds to " << invalid_char << " is not found." << std::endl;
}
