#include "sequence.h"

#include <iostream>
#include <fstream>

Sequence::Sequence(const std::string &standard_sequence) :
sequence_file{standard_sequence},
current_seq_idx{0} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Sequence Constructor" << std::endl;
#endif
    try {
        update_sequence();
    } catch (EmptySequenceException &err) {
        throw err;
    }
}

Sequence::~Sequence() {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Sequence Destructor" << std::endl;
#endif
}

void Sequence::update_sequence() {
    BlockShapeUtil util;
    std::vector<BlockShape> temp_seq;
    char temp_block;
    std::ifstream reader{sequence_file};
    while (reader >> temp_block) {
        if (temp_block == ' ') continue;
        BlockShape temp_blockShape;
        try {
            temp_blockShape = util.to_block_shape(temp_block);
        } catch (InvalidSymbolicCharException &err) {
            std::cerr << temp_block << " is invalid block" << std::endl;
            continue;
        }
        temp_seq.push_back(temp_blockShape);
    }
    if (temp_seq.empty()) {
        throw EmptySequenceException{"Given sequence file is invalid"};
    }
    sequence.swap(temp_seq);
    current_seq_idx = 0;
}

void Sequence::set_sequence(const std::string &new_sequence_file) {
    sequence_file = new_sequence_file;
    try {
        update_sequence();
    } catch (EmptySequenceException &err) {
        throw err;
    }
}

BlockShape Sequence::get_next_block() {
    if (sequence.empty()) throw EmptySequenceException{"Sequence file is empty"};
    if (current_seq_idx == sequence.size()) current_seq_idx = 0;
    return sequence[current_seq_idx++];
}

EmptySequenceException::EmptySequenceException(const std::string &msg) : msg{msg} {}

std::string EmptySequenceException::what() const noexcept {
    return msg;
}