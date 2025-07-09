#include "heavy.h"

Heavy::Heavy(TetrisAbstract *component, int heaviness) : TetrisDecorator(component), heaviness{heaviness} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Heavy Constructor" << std::endl;
#endif
}

bool Heavy::left(int step) {
    component->left(step);
    for (int i = 0; i < heaviness; i++) {
        if (!component->down(1)) {
            return true;
        }
    }
    return false;
}

bool Heavy::right(int step) {
    component->right(step);
    for (int i = 0; i < heaviness; i++) {
        if (!component->down(1)) {
            return true;
        }
    }
    return false;
}

bool Heavy::down(int step) {
    return component->down(step);
}

void Heavy::clockwise(int step) {
    component->clockwise(step);
}

void Heavy::counter_clockwise(int step) {
    component->counter_clockwise(step);
}

bool Heavy::drop(int step) {
    return component->drop(step);
}

Grid *Heavy::getGrid() {
    return component->getGrid();
}

int Heavy::getScore() {
    return component->getScore();
}

int Heavy::getNextLevel() {
    return component->getNextLevel();
}

void Heavy::setBlind(bool _blind) {
    component->setBlind(_blind);
}

bool Heavy::isBlind() {
    return component->isBlind();
}

void Heavy::level_up(int step) {
    component->level_up(step);
}

void Heavy::level_down(int step) {
    component->level_down(step);
}

void Heavy::random() {
    component->random();
}

void Heavy::noRandom(const std::string &sequence_file) {
    component->noRandom(sequence_file);
}

void Heavy::changeCurrentBlock(BlockShape type) {
    component->changeCurrentBlock(type);
}

bool Heavy::isHeavy() {
    return true;
}

std::vector<std::pair<int, int>> Heavy::getNextShape() {
    return component->getNextShape();
}

Block * Heavy::getNextBlock() {
    return component->getNextBlock();
}

bool Heavy::isOver() {
    return component->isOver();
}



