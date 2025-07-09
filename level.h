#ifndef __LEVEL_H__
#define __LEVEL_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "sequence.h"
#include "blockShape.h"
#include <vector>
#include <stdexcept>

class Tetris;

class Level {
protected:
    Sequence seq;
    bool rand;
    int seed;

public:
    explicit Level(std::string standard_sequence_file, bool rand, int seed);
    virtual ~Level();

    virtual BlockShape getNextBlock() = 0;

    virtual void noRandom(const std::string &file_name) = 0;

    virtual void random() = 0;

    virtual void action_left(Tetris *tetris) = 0;
    virtual void action_right(Tetris *tetris) = 0;
    virtual void action_down(Tetris *tetris) = 0;
    virtual void action_drop(Tetris *tetris, int row_cleared) = 0;
    virtual void action_clockwise(Tetris *tetris) = 0;
    virtual void action_counter_clockwise(Tetris *tetris) = 0;
};

#endif

#if 0

#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <vector>
#include <stdexcept>

class BlockShape;

class Level {
protected:
    int level;
    std::string filename;
    bool rand;

    std::vector<char> blkseq;

public:
    virtual Level(int level, std::string file = "", bool rand = false);
    virtual BlockShape getNextBlock () = 0;
    void readFile();
    virtual ~Level();
};

class InvalidArgumentException : public std::exception {
public:
    // CONSTRUCTOR: InvalidArgumentException
    explicit InvalidArgumentException() = default;
};

#endif
#endif