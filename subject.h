#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include <string>
#include "subscription.h"
#include "action.h"

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

class UserInterface;

class Observer;

class Subject {
protected:
    std::vector<Observer*> observers;
public:
    void attach(Observer *o);
    virtual void notifyObservers(SubscriptionType sub, Action action, UserInterface *ui) = 0;
};

#endif
