#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include <iostream>
#include <vector>

#include "observer.h"
#include "grid.h"

class Block;
class UserInterface;
class Tetris;

class TextDisplay : public Observer {
    UserInterface *ui;
    const int width = 11;
    const int height = 18;

    std::vector<std::vector<char>> D0;

    std::vector<std::vector<char>> D1;

    std::vector<int> blindList;

    void updateGame();

public:
    explicit TextDisplay(UserInterface *ui);
    ~TextDisplay();
    void update(Tetris &whoNotified, Action action) override; // for next
    void update(UserInterface &whoNotified, Action action) override;
    SubscriptionType subType() const override;
    void addBlind(int player);
    void removeBlind(int player);

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};



#endif