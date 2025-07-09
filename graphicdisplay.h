#ifndef __GRAPHICDISPLAY_H__
#define __GRAPHICDISPLAY_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "subject.h"
#include "observer.h"
#include "window.h"
#include "action.h"

#include <string>

class UserInterface;

class GraphicDisplay : public Observer {

    std::vector<std::vector<Color>> p0;
    std::vector<std::vector<Color>> next0;

    std::vector<std::vector<Color>> p1;
    std::vector<std::vector<Color>> next1;

    bool graphicOn;
    bool blindOn = false;

    Xwindow *xw;
    UserInterface *ui;

    const int game_height = 18;
    const int game_width = 11;
    const int next_height = 2;
    const int next_width = 4;

    int height = 630;
    int width = 900;
    int s_height = 75; // score = s
    int s_width = 330;
    int b_height = 540;
    int b_width = 330;
    int hi_height = 75; // high score = hi
    int hi_width = 220;
    int msg_height = 120;
    int msg_width = 220;
    int c_height = 415; // command = c
    int c_width = 220;
    int blk_length = 30;
    int blk = 30 * 0.99;
    int space = 5;

    std::vector<int> blindList;

    void updatep0(bool);
    void updatep1(bool);

public:
    // Constructor, Destructor
    GraphicDisplay(UserInterface *ui, bool _graphicOn = true);
    ~GraphicDisplay();

    void setup();

    // Observer override
    void update(Tetris&, Action action) override;
    void update(UserInterface&, Action action) override;

    SubscriptionType subType() const override;

    // Blind special action
    void addBlind(int);
    void removeBlind(int);


};
#endif

