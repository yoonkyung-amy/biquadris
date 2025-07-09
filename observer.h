#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "subscription.h"
#include "subject.h"
#include <string>

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

class Grid;
class Tetris;
class UserInterface;

class Observer { // abstract base class
    public:
    virtual void update(Tetris &s, Action action) = 0;
    virtual void update(UserInterface &s, Action action) = 0;
    virtual SubscriptionType subType() const = 0;
    virtual ~Observer() = default;
};

 #endif
