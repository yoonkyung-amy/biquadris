#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include <string>
#include "blockShape.h"

class Sequence {
    std::string sequence_file;
    std::vector<BlockShape> sequence;
    unsigned int current_seq_idx;

    void update_sequence();
public:
    explicit Sequence(const std::string &standard_sequence);

    ~Sequence();

    void set_sequence(const std::string &new_sequence_file);

    BlockShape get_next_block();
};

class EmptySequenceException {
    std::string msg;
public:
    explicit EmptySequenceException(const std::string &msg);

    std::string what() const noexcept;
};

#endif
