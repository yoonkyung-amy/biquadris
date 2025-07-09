#include "subject.h"
#include "userInterface.h"
#include "observer.h"
#include <iostream>

void Subject::attach( Observer *o ) {
    // puts the observers back to the list(vector)
    observers.emplace_back(o);
}
