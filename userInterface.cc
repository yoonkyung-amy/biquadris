#include "userInterface.h"
#include "observer.h"
#include "subject.h"
#include <fstream>

UserInterface::UserInterface(std::vector<std::string> &seq, int seed, int initial_levels, bool _graphicOn) :
high_score{0},
players{static_cast<int>(seq.size())},
current_player{0},
heaviness{2},
graphicOn{_graphicOn},
seed{seed},
msg{"Player 1's turn!"},
isGameOver{false} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "User Interface Constructor" << std::endl;
#endif
    for (int i = 0; i < players; i++) {
        games.emplace_back(new Tetris{seq[i], seed, initial_levels});
        grid.push_back(games[i]->getGrid());
        plain_games.push_back(games[i]);
    }
    backup_seq = seq;
    backup_initial_level = initial_levels;
    TD = new TextDisplay{this};
    GD = new GraphicDisplay{this, graphicOn};

    observers.emplace_back(TD);
    if (graphicOn) {
        observers.emplace_back(GD);
    }
    notifyObservers(SubscriptionType::Display, Action::updateNext, this);
    notifyObservers(SubscriptionType::Display, Action::updateCurrent, this);
    printDisplay();
}

UserInterface::~UserInterface() {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "User Interface Destructor" << std::endl;
#endif
    for (auto & i : grid) {
        i = nullptr;
    }
    for (int i = 0; i < players; i++) {
        if (games[i]->isHeavy()) {
            delete games[i];
            games[i] = plain_games[i];
        }
    }
    for (int i = 0; i < players; i++) {
        delete games[i];
    }
    delete TD;
    delete GD;
}

void UserInterface::printDisplay() {
    std::cout << *TD << std::endl;
}

void UserInterface::endTurn() {
    if (++current_player >= players) current_player = 0;
    msg = "Player " + std::to_string(current_player + 1) + "'s turn!";
}

void UserInterface::setGraphic(bool _graphic) {
    graphicOn = _graphic;
}

void UserInterface::right(int step) {
    if (games[current_player]->right(step) && games[current_player]->isHeavy()) {
        drop();
    }

    if (games[current_player]->isBlind()) {
        notifyObservers(SubscriptionType::Display, Action::blind, this);
    } else {
        notifyObservers(SubscriptionType::Display, Action::updateCurrent, this);
    }

    printDisplay();
}

void UserInterface::left(int step) {
    if (games[current_player]->left(step) && games[current_player]->isHeavy()) {
        drop();
    }

    if (games[current_player]->isBlind()) {
        notifyObservers(SubscriptionType::Display, Action::blind, this);
    } else {
        notifyObservers(SubscriptionType::Display, Action::updateCurrent, this);
    }

    printDisplay();
}

void UserInterface::down(int step) {
    games[current_player]->down(step);

    if (games[current_player]->isBlind()) {
        notifyObservers(SubscriptionType::Display, Action::blind, this);
    } else {
        notifyObservers(SubscriptionType::Display, Action::updateCurrent, this);
    }

    printDisplay();
}

bool UserInterface::drop(int step) {
    bool result = games[current_player]->drop(step);
    int score = games[current_player]->getScore();
    if (score > high_score) {
        high_score = score;
    }
    if (games[current_player]->isHeavy()) {
        delete games[current_player];
        games[current_player] = plain_games[current_player];
    }

    if (games[current_player]->isBlind()) {
        TD->removeBlind(current_player);
        GD->removeBlind(current_player);
        games[current_player]->setBlind(false);
    }

    if (games[current_player]->isOver()) {
        // TODO: Game is over do something
        isGameOver = true;
        restart();
    }
    int nextplayer = current_player;
    if (++nextplayer >= players) nextplayer = 0;
    msg = "Player " + std::to_string(nextplayer + 1) + "'s turn!";
    notifyObservers(SubscriptionType::Display, Action::score, this);
    notifyObservers(SubscriptionType::Display, Action::updateCurrent, this);

    endTurn();

    printDisplay();

    if (result) {
        return true;
    } else {
        return false;
    }
}

void UserInterface::clockwise(int step) {
    games[current_player]->clockwise(step);

    if (games[current_player]->isBlind()) {
        notifyObservers(SubscriptionType::Display, Action::blind, this);
    } else {
        notifyObservers(SubscriptionType::Display, Action::updateCurrent, this);
    }

    printDisplay();
}

void UserInterface::counter_Clockwise(int step) {
    games[current_player]->counter_clockwise(step);

    if (games[current_player]->isBlind()) {
        notifyObservers(SubscriptionType::Display, Action::blind, this);
    } else {
        notifyObservers(SubscriptionType::Display, Action::updateCurrent, this);
    }

    printDisplay();
}

void UserInterface::level_up(int step) {
    games[current_player]->level_up(step);

    if (games[current_player]->isBlind()) {
        notifyObservers(SubscriptionType::Display, Action::blind, this);
    } else {
        notifyObservers(SubscriptionType::Display, Action::score, this);
    }

    printDisplay();
}

void UserInterface::level_down(int step) {
    games[current_player]->level_down(step);

    if (games[current_player]->isBlind()) {
        notifyObservers(SubscriptionType::Display, Action::blind, this);
    } else {
        notifyObservers(SubscriptionType::Display, Action::score, this);
    }

    printDisplay();
}

void UserInterface::random() {
    games[current_player]->random();

    if (games[current_player]->isBlind()) {
        notifyObservers(SubscriptionType::Display, Action::blind, this);
    } else {
        notifyObservers(SubscriptionType::Display, Action::updateCurrent, this);
    }

    printDisplay();
}

void UserInterface::noRandom(const std::string &seq) {
    games[current_player]->noRandom(seq);

    if (games[current_player]->isBlind()) {
        notifyObservers(SubscriptionType::Display, Action::blind, this);
    } else {
        notifyObservers(SubscriptionType::Display, Action::updateCurrent, this);
    }

    printDisplay();
}

void UserInterface::change(BlockShape type) {
    games[current_player]->changeCurrentBlock(type);

    if (games[current_player]->isBlind()) {
        notifyObservers(SubscriptionType::Display, Action::blind, this);
    } else {
        notifyObservers(SubscriptionType::Display, Action::updateCurrent, this);
    }

    printDisplay();
}

void UserInterface::apply_heavy() {
//    int next_player = current_player;
//    if (++next_player >= players) next_player = 0;
    games[current_player] = new Heavy{games[current_player], heaviness};
}

void UserInterface::apply_blind() {
//   games[this->getNextPlayer()]->setBlind(true);
    games[current_player]->setBlind(true);
    std::cout << "Player " << current_player << "Blind applied" << std::endl;
    TD->addBlind(current_player);
    GD->addBlind(current_player);
    notifyObservers(SubscriptionType::Display, Action::blind, this);
    printDisplay();
}

void UserInterface::apply_force(BlockShape type) {
//    int next_player = current_player;
//    if (++next_player >= players) next_player = 0;
    games[current_player]->changeCurrentBlock(type);
    notifyObservers(SubscriptionType::Display, Action::updateCurrent, this);
    notifyObservers(SubscriptionType::Display, Action::updateNext, this);
    printDisplay();
}

void UserInterface::restart() {
    for (auto & i : grid) {
        i = nullptr;
    }
    for (int i = 0; i < players; i++) {
        if (games[i]->isHeavy()) {
            delete games[i];
            games[i] = plain_games[i];
        }
    }
    for (int i = 0; i < players; i++) {
        delete games[i];
    }
    for (int i = 0; i < players; i++) {
        games[i] = new Tetris{backup_seq[i], seed, backup_initial_level};
        grid[i] = (games[i]->getGrid());
        plain_games[i] = games[i];
    }

    int store = current_player;
    current_player = 0;
    if (isGameOver) {
        int nextplayer = store;
        if (++nextplayer >= players) nextplayer = 0;
        msg = "Player " + std::to_string(nextplayer + 1) + " WON!";
    } else {
        msg = "Player " + std::to_string(current_player + 1) + "'s turn!";
    }
    notifyObservers(SubscriptionType::Display, Action::reset, this);
    printDisplay();
}

TextDisplay* UserInterface::getTD() {
    return TD;
}

void UserInterface::notifyObservers(SubscriptionType sub, Action action, UserInterface *ui) {
   for (int i = 0; i < observers.size(); i++) {
       if (observers[i]->subType() == sub) {
          observers[i]->update(*this, action);
       }
   }
}

int UserInterface::getHiScore() {
    return high_score;
}

std::string UserInterface::getMessage() const noexcept {
    return msg;
}
