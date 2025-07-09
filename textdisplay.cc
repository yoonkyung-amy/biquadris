#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "textdisplay.h"
#include "observer.h"
#include "subject.h"
#include "grid.h"
#include "tetris.h"
#include "userInterface.h"
#include "blockShape.h"

TextDisplay::TextDisplay(UserInterface *ui) :
        ui{ui} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Text Display Constructor" << std::endl;
#endif
    D0.assign(height, std::vector<char>(width, ' '));
    D1.assign(height, std::vector<char>(width, ' '));

}

TextDisplay::~TextDisplay() {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "TextDisplay Destructor" << std::endl;
#endif
}

void TextDisplay::addBlind(int player) {
    bool exist = false;
    for (int i = 0; i < blindList.size(); ++i) {
        if (blindList[i] == player) exist = true;
    }
    if (!exist) blindList.push_back(player);
}

void TextDisplay::removeBlind(int player) {
    for (int i = 0; i < blindList.size(); ++i) {
        if (blindList[i] == player) blindList.erase(blindList.begin() + i);
    }
}

void TextDisplay::updateGame() {
    auto grids = ui->getGrids();
    BlockShapeUtil util;

    // player 0
    for (int row = 0; row < ui->getGrids()[0]->getHeight(); row++) {
        for (int col = 0; col < ui->getGrids()[0]->getWidth(); col++) {
            if (ui->getGrids()[0]->getBoard(row, col) == nullptr) {
                D0[row][col] = ' ';
            } else {
                D0[row][col] = util.to_char(ui->getGrids()[0]->getBoard(row, col)->getType());
            }
        }
    }

    // player 0's next block

    // player 1
    for (int row = 0; row < ui->getGrids()[1]->getHeight(); row++) {
        for (int col = 0; col < ui->getGrids()[1]->getWidth(); col++) {
            if (ui->getGrids()[1]->getBoard(row, col) == nullptr) {
                D1[row][col] = ' ';
            } else {
                D1[row][col] = util.to_char(ui->getGrids()[1]->getBoard(row, col)->getType());
            }
        }
    }

    // player 1's next block

}



void TextDisplay::update(Tetris &whoNotified, Action action) {
}


void TextDisplay::update(UserInterface &whoNotified, Action action) {
    auto grids = whoNotified.getGrids();
    int current = whoNotified.getCurrentPlayer();
    int next = whoNotified.getNextPlayer();

    BlockShapeUtil util;

    if (action == Action::updateCurrent || action == Action::updateNext) {
        updateGame();
    }
    else if (action == Action::blind) {
        for (int i = 0; i < blindList.size(); ++i) {
            for (int row = 0; row < grids[blindList[i]]->getHeight(); row++) {
                for (int col = 0; col < grids[blindList[i]]->getWidth(); col++) {
                    if ((3 - 1) <= col && col <= (9 - 1) && (3 + 3) <= row && row <= (12 + 3)) {
                        if (blindList[i] == 0) {
                            D0[row][col] = '?';
                        } else {
                            D1[row][col] = '?';
                        }
                    } else if (grids[blindList[i]]->getBoard(row, col) == nullptr) {
                        if (blindList[i] == 0) {
                            D0[row][col] = ' ';
                        } else {
                            D1[row][col] = ' ';
                        }
                    } else {
                        if (blindList[i] == 0) {
                            D0[row][col] = util.to_char(grids[blindList[i]]->getBoard(row, col)->getType());
                        } else {
                            D1[row][col] = util.to_char(grids[blindList[i]]->getBoard(row, col)->getType());
                        }
                    }

                }
            }
        }
    }
    else if (action == Action::reset) {
        for (int i = 0; i < width; ++i) {
            D0[i].clear();
            D1[i].clear();
        }
        D0.clear();
        D1.clear();
        D0.assign(height, std::vector<char>(width, ' '));
        D1.assign(height, std::vector<char>(width, ' '));
        updateGame();
    }
}

SubscriptionType TextDisplay::subType() const {
    return SubscriptionType::Display;
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    std::string space = "       ";
    std::string divider = "-----------";
    BlockShapeUtil util;

    // MESSAGE
    out << space << td.ui->getMessage() << space << std::endl;

    // HIGHSCORE
    out << "[" << "     " << "High Score: ";
    out << std::setfill(' ') << std::setw(5) << td.ui->getHiScore() << "     " << "]" << std::endl;

    out << "Level:" << std::setfill(' ') << std::setw(5) << td.ui->getLevel(0) << space;
    out << "Level:" << std::setfill(' ') << std::setw(5) << td.ui->getLevel(1) << std::endl;

    out << "Score:" << std::setfill(' ') << std::setw(5) << td.ui->getScore(0) << space;
    out << "Score:" << std::setfill(' ') << std::setw(5) << td.ui->getScore(1) << std::endl;

    out << divider << space << divider << std::endl;

    for (int i = 0; i < td.height; ++i) {
        for (int j = 0; j < td.width; ++j) {
            out << td.D0[i][j];
        }
        out << space;
        for (int k = 0; k < td.width; ++k) {
            out << td.D1[i][k];
        }
        out << std::endl;
    }

    out << divider << space << divider << std::endl;
    out << "Next:      " << space << "Next:" << std::endl;

    auto shape_0 = td.ui->getNextShape(0);
    auto shape_1 = td.ui->getNextShape(1);
    for (int row = 1; row >= 0; row--) {
        for (int col = 0; col < td.ui->getGrids()[0]->getWidth(); ++col) {
            bool found = false;
            for (int i = 0; i < shape_0.size(); i++) {
                if (shape_0[i].first == row && shape_0[i].second == col) {
                    found = true;
                }
            }
            if (found) {
                out << util.to_char(td.ui->getNextBlock(0)->getType());
            } else {
                out << " ";
            }
        }
        out << space;
        for (int col = 0; col < td.ui->getGrids()[1]->getWidth(); ++col) {
            bool found = false;
            for (int i = 0; i < shape_1.size(); i++) {
                if (shape_1[i].first == row && shape_1[i].second == col) {
                    found = true;
                }
            }
            if (found) {
                out << util.to_char(td.ui->getNextBlock(1)->getType());
            } else {
                out << " ";
            }
        }
        out << std::endl;
    }
    return out;
}

