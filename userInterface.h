#ifndef __USER_INTERFACE_H__
#define __USER_INTERFACE_H__

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "tetris.h"
#include "heavy.h"
#include "subject.h"
#include "subscription.h"
#include "textdisplay.h"
#include "graphicdisplay.h"

class UserInterface : public Subject {
    std::vector<TetrisAbstract*> games;
    std::vector<TetrisAbstract*> plain_games;
    std::vector<Grid*> grid;
    int high_score;
    const int players;
    int current_player;
    const int heaviness;
    std::vector<std::string> backup_seq;
    int backup_initial_level;
    bool graphicOn;
    std::string msg;
    int seed;
    bool isGameOver;

    TextDisplay *TD;
    GraphicDisplay *GD;

    void printDisplay();
public:
    explicit UserInterface(std::vector<std::string> &seq, int seed, int initial_levels, bool graphicOn = true);

    ~UserInterface();

    void endTurn();

    void right(int step = 1);

    void left(int step = 1);

    void down(int step = 1);

    bool drop(int step = 1);

    void clockwise(int step = 1);

    void counter_Clockwise(int step = 1);

    void level_up(int step = 1);

    void level_down(int step = 1);

    void random();

    void noRandom(const std::string &seq);

    void change(BlockShape type);

    void apply_heavy();

    void apply_blind();

    void apply_force(BlockShape type);

    void restart();

    std::vector<Grid*> getGrids() {
        return grid;
    }

    std::vector<std::pair<int, int>> getNextShape(int player) {
        return games[player]->getNextShape();
    }

    int getCurrentPlayer() const noexcept {
        return current_player;
    }

    int getNextPlayer() const noexcept {
        int next_player = current_player;
        if (++next_player >= players) next_player = 0;
        return next_player;
    }

    int getLevel(int player) const noexcept {
        return games[player]->getNextLevel();
    }

    int getScore(int player) const noexcept {
        return games[player]->getScore();
    }

    Block* getNextBlock(int player) {
        return games[player]->getNextBlock();
    }

    int getHiScore();

    TextDisplay* getTD();

    void setGraphic(bool _graphic);

    void notifyObservers(SubscriptionType sub, Action action, UserInterface *ui) override;

    std::string getMessage() const noexcept;

};

#endif


