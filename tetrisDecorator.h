#ifndef __TETRIS_DECORATOR_H__
#define __TETRIS_DECORATOR_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "tetrisAbstract.h"

class TetrisDecorator : public TetrisAbstract{
protected:
    TetrisAbstract *component;
public:
    TetrisDecorator(TetrisAbstract *component);
    virtual ~TetrisDecorator();
};

#endif
