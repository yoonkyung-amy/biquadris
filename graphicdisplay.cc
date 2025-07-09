#include <iostream>
#include <string>

#include "graphicdisplay.h"
#include "userInterface.h"
#include "window.h"
#include "observer.h"
#include "subject.h"

// Constructor
GraphicDisplay::GraphicDisplay(UserInterface *ui, bool _graphicOn)
        : xw{nullptr}, ui{ui}, graphicOn{_graphicOn} {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Graphic Display Constructor" << std::endl;
#endif

    if (graphicOn) {
        xw = new Xwindow{};

        p0.assign(game_height, std::vector<Color>(game_width, Color::DimGray));
        next0.assign(next_height, std::vector<Color>(next_width, Color::DimGray));

        p1.assign(game_height, std::vector<Color>(game_width, Color::DimGray));
        next1.assign(next_height, std::vector<Color>(next_width, Color::DimGray));

        setup();
    }
}

// Destructor
GraphicDisplay::~GraphicDisplay() {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Graphic Display Destructor" << std::endl;
#endif
    if (xw != nullptr) delete xw;
}

SubscriptionType GraphicDisplay::subType() const {
    return SubscriptionType::Display;
}

// All the basic setup here
void GraphicDisplay::setup() {

// Background
    xw->fillRectangle(0, 0, width, height, Color::Gray);

    // PLAYER 0
    xw->fillRectangle(5, 85, b_width, b_height, Color::DimGray); // Board
    xw->fillRectangle(5, 5, s_width, s_height, Color::WhiteSmoke); //  level, score, next
    xw->drawString(30, 30, "LEVEL: "); // Level
    std::string level_0 = std::to_string(ui->getLevel(0));
    xw->drawString(70, 30, level_0); // init level
    xw->drawString(30, 60, "SCORE: "); // Score
    std::string score_0 = std::to_string(ui->getScore(0));
    xw->drawString(70, 60, score_0); // init score
    xw->drawString(165, 45, "NEXT: "); // next
    xw->fillRectangle(b_width - 130, 7.5, 130, 70, Color::DimGray);
    // sample next
    //xw->fillRectangle(205, 10 + blk_length, blk, blk, Color::Blue); // bottom-left
    //xw->fillRectangle(205 + (blk_length * 1), 10 + blk_length, blk, blk, Color::Blue);
    //xw->fillRectangle(205 + (blk_length * 2), 10 + blk_length, blk, blk, Color::Blue);
    //xw->fillRectangle(205 + (blk_length * 3), 10 + blk_length, blk, blk, Color::Blue);


    // PLAYER 1
    xw->fillRectangle((width - b_width - space), 85, b_width, b_height, Color::DimGray); //Board
    xw->fillRectangle(width - s_width - 5, 5, s_width, s_height, Color::WhiteSmoke); // level, score, next
    xw->drawString(width - s_width + 20, 30, "LEVEL: "); // level
    std::string level_1 = std::to_string(ui->getLevel(1));
    xw->drawString(width - s_width + 60, 30, level_1); // sample level
    xw->drawString(width - s_width + 20, 60, "SCORE: "); // score
    std::string score_1 = std::to_string(ui->getScore(1));
    xw->drawString(width - s_width + 60, 60, score_1); // sample score
    xw->drawString(725, 45, "NEXT: "); // next
    xw->fillRectangle(width - b_width + 130 + 60, 7.5, 130, 70, Color::DimGray);
    // sample next
    // xw->fillRectangle(765, 10 + blk_length, blk, blk, Color::Maroon); // bottom left
    //xw->fillRectangle(765 + blk_length, 10 + blk_length, blk, blk, Color::Maroon);
    //xw->fillRectangle(765 + (blk_length * 2), 10 + blk_length, blk, blk, Color::Maroon);
    //xw->fillRectangle(765 + blk_length, 10, blk, blk, Color::Maroon);
    //xw->fillRectangle(765, 10, blk, blk, Color::Maroon);


    // Hi Score
    xw->fillRectangle(s_width + 10,5, hi_width, hi_height, Color::WhiteSmoke);
    xw->drawString(b_width + 35, 5 + (hi_height / 2), "Hi Score: ");
    std::string hi_score = std::to_string(ui->getHiScore());
    xw->drawString(b_width + 95, 5 + (hi_height / 2), hi_score);

    // Hi Players
    xw->fillRectangle(b_width + 10, 85, msg_width, msg_height, Color::White);
    xw->drawString(b_width + 30, 120, "Welcome to Biquadris");
    xw->drawString(b_width + 30, 160, "Hi, Players!");

    // Command
    xw->fillRectangle(b_width + 10, 90 + msg_height, c_width, c_height, Color::White);
    xw->drawString(b_width + 20, 170 + (msg_height / 2), "Command List");
    xw->drawString(b_width + 20, 170 + (msg_height / 2) + 30, "Movement commands can take");

    xw->drawString(b_width + 20, 170 + (msg_height / 2) + (30 * 2), "!#@!#!");
    xw->drawString(b_width + 20, 170 + (msg_height / 2) + (30 * 3), "left");

    // SAMPLE BLK on P1 Board
    //xw->fillRectangle(5, 85, blk, blk, Color::Red);
    //xw->fillRectangle(5, 85 + blk_length, blk, blk, Color::Red);
    //xw->fillRectangle(5 + blk_length, 85, blk, blk, Color::Red);


    // SAMPLE BLK on P2 Board
    //xw->fillRectangle(width - b_width - space, 85, blk, blk, Color::Purple);
    //xw->fillRectangle(width - b_width - space + blk_length, 85, blk, blk, Color::Purple);
}

void GraphicDisplay::updatep0(bool level) {

    if (level) {
        xw->fillRectangle(5, 5, 140, s_height, Color::WhiteSmoke); //  level, score, next
        xw->drawString(30, 30, "LEVEL: "); // Level

        //xw->fillRectangle(70, 30, 50, 40, Color::WhiteSmoke);

        std::string level_0 = std::to_string(ui->getLevel(0));

        xw->drawString(70, 30, level_0); // init level

        xw->drawString(30, 60, "SCORE: "); // Score
        std::string score_0 = std::to_string(ui->getScore(0));
        xw->drawString(70, 60, score_0); // init score


        if (ui->getScore(0) == ui->getHiScore()) {
            xw->fillRectangle(s_width + 10, 5, hi_width, hi_height, Color::WhiteSmoke);
            xw->drawString(b_width + 35, 5 + (hi_height / 2), "Hi Score: ");
            std::string hi_score = std::to_string(ui->getHiScore());
            xw->drawString(b_width + 95, 5 + (hi_height / 2), hi_score);
        }

    } else {
        for (int row = 0; row < ui->getGrids()[0]->getHeight(); row++) {
            for (int col = 0; col < ui->getGrids()[0]->getWidth(); col++) {
                if (ui->getGrids()[0]->getBoard(row, col) == nullptr) {
                    if (p0[row][col] != Color::DimGray) {
                        p0[row][col] = Color::DimGray;
                        xw->fillRectangle(5 + (col * blk_length), 85 + (row * blk_length), blk, blk, Color::DimGray);
                    }
                } else {
                    Color t = ui->getGrids()[0]->getBoard(row, col)->getColor();
                    if (p0[row][col] != t) {
                        p0[row][col] = t;
                        xw->fillRectangle(5 + (col * blk_length), 85 + (row * blk_length), blk, blk, t);
                    }
                }
            }
        }
    }

    // next block
    auto shape_0 = ui->getNextShape(0);
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 4; ++col) {
            bool found = false;
            for (int i = 0; i < shape_0.size(); i++) {
                if (1 - shape_0[i].first == row && shape_0[i].second == col) {
                    found = true;
                }
            }
            if (found) {
                Color t = ui->getNextBlock(0)->getColor();
                if (next0[row][col] != t) {
                    next0[row][col] = t;
                    xw->fillRectangle(205 + (col * blk_length), 10 + (row * blk_length), blk, blk,
                                      t); // bottom-left
                }
            } else {
                if (next0[row][col] != Color::DimGray) {
                    next0[row][col] = Color::DimGray;
                    xw->fillRectangle(205 + (col * blk_length), 10 + (row * blk_length), blk, blk, Color::DimGray);
                }
            }
        }
    }
}

void GraphicDisplay::updatep1(bool level) {
    if (level) {
        xw->fillRectangle(width - s_width - 5, 5, 140, s_height, Color::WhiteSmoke);
        xw->drawString(width - s_width + 20, 30, "LEVEL: "); // level

        std::string level_1 = std::to_string(ui->getLevel(1));
        xw->drawString(width - s_width + 60, 30, level_1); // sample level

        xw->drawString(width - s_width + 20, 60, "SCORE: "); // score
        std::string score_1 = std::to_string(ui->getScore(1));
        xw->drawString(width - s_width + 60, 60, score_1); // sample score

        if (ui->getScore(1) == ui->getHiScore()) {
            xw->fillRectangle(s_width + 10, 5, hi_width, hi_height, Color::WhiteSmoke);
            xw->drawString(b_width + 35, 5 + (hi_height / 2), "Hi Score: ");
            std::string hi_score = std::to_string(ui->getHiScore());
            xw->drawString(b_width + 95, 5 + (hi_height / 2), hi_score);
        }
    } else {
        for (int row = 0; row < ui->getGrids()[1]->getHeight(); row++) {
            for (int col = 0; col < ui->getGrids()[1]->getWidth(); col++) {
                if (ui->getGrids()[1]->getBoard(row, col) == nullptr) {
                    if (p1[row][col] != Color::DimGray) {
                        p1[row][col] = Color::DimGray;
                        xw->fillRectangle(width - b_width - space + (col * blk_length),
                                          85 + (row * blk_length), blk, blk, Color::DimGray);
                    }
                } else {
                    Color t = ui->getGrids()[1]->getBoard(row, col)->getColor();
                    if (p1[row][col] != t) {
                        p1[row][col] = t;
                        xw->fillRectangle(width - b_width - space + (col * blk_length),
                                          85 + (row * blk_length), blk, blk, t);
                    }
                }
            }
        }
    }

    // next block
    auto shape_1 = ui->getNextShape(1);
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 4; ++col) {
            bool found = false;
            for (int i = 0; i < shape_1.size(); i++) {
                if (1 - shape_1[i].first == row && shape_1[i].second == col) {
                    found = true;
                }
            }
            if (found) {
                Color t = ui->getNextBlock(1)->getColor();
                if (next1[row][col] != t) {
                    next1[row][col] = t;
                    xw->fillRectangle(765 + (col * blk_length), 10 + (row * blk_length), blk, blk,
                                      t); // bottom-left
                }
            } else {
                if (next1[row][col] != Color::DimGray) {
                    next1[row][col] = Color::DimGray;
                    xw->fillRectangle(765 + (col * blk_length), 10 + (row * blk_length), blk, blk, Color::DimGray);
                }
            }
        }
    }
}


// Updating
void GraphicDisplay::update(Tetris& WhoNotified, Action action) {}

void GraphicDisplay::addBlind(int player) {
    bool exist = false;
    for (int i = 0; i < blindList.size(); ++i) {
        if (blindList[i] == player) exist = true;
    }
    if (!exist) blindList.push_back(player);
}

void GraphicDisplay::removeBlind(int player) {
    for (int i = 0; i < blindList.size(); ++i) {
        if (blindList[i] == player) blindList.erase(blindList.begin() + i);
    }
}

void GraphicDisplay::update(UserInterface& WhoNotified, Action action) {
    if (graphicOn) {
        xw->fillRectangle(b_width + 10, 85, msg_width, msg_height, Color::White);
        xw->drawString(b_width + 30, 135, ui->getMessage());

        if (action == Action::updateCurrent) {
            if (WhoNotified.getCurrentPlayer() == 0) {
                updatep0(false);
            } else {
                updatep1(false);
            }
        } else if (action == Action::updateNext) {
            if (WhoNotified.getNextPlayer() == 0) {
                updatep0(false);
            } else {
                updatep1(false);
            }
        } else if (action == Action::score) {
            if (WhoNotified.getCurrentPlayer() == 0) {
                updatep0(true);
            } else {
                updatep1(true);
            }
        } else if (action == Action::reset) {
            updatep0(false);
            updatep0(true);
            updatep1(false);
            updatep1(true);
        }
            /// Blind ///
        else if (action == Action::blind) {
            for (int i = 0; i < blindList.size(); ++i) {
                for (int row = 0; row < ui->getGrids()[blindList[i]]->getHeight(); row++) {
                    for (int col = 0; col < ui->getGrids()[blindList[i]]->getWidth(); col++) {
                        if ((3 - 1) <= col && col <= (9 - 1) && (3 + 3) <= row && row <= (12 + 3)) {
                            if (blindList[i] == 0) {
                                if (p0[row][col] != Color::White) {
                                    p0[row][col] = Color::White;
                                    xw->fillRectangle(5 + (col * blk_length), 85 + (row * blk_length), blk, blk,
                                                      Color::White);
                                }
                            } else {
                                if (p1[row][col] != Color::White) {
                                    p1[row][col] = Color::White;
                                    xw->fillRectangle(width - b_width - space + (col * blk_length),
                                                      85 + (row * blk_length), blk, blk, Color::White);
                                }
                            }
                        } else if (ui->getGrids()[blindList[i]]->getBoard(row, col) == nullptr) {
                            if (blindList[i] == 0) {
                                if (p0[row][col] != Color::DimGray) {
                                    p0[row][col] = Color::DimGray;
                                    xw->fillRectangle(5 + (col * blk_length), 85 + (row * blk_length), blk, blk,
                                                      Color::DimGray);
                                }
                            } else {
                                if (p1[row][col] != Color::DimGray) {
                                    p1[row][col] = Color::DimGray;
                                    xw->fillRectangle(width - b_width - space + (col * blk_length),
                                                      85 + (row * blk_length), blk, blk, Color::DimGray);
                                }
                            }
                        } else {
                            if (blindList[i] == 0) {
                                Color t = ui->getGrids()[0]->getBoard(row, col)->getColor();
                                if (p0[row][col] != t) {
                                    p0[row][col] = t;
                                    xw->fillRectangle(5 + (col * blk_length), 85 + (row * blk_length), blk, blk, t);
                                }
                            } else {
                                Color t = ui->getGrids()[1]->getBoard(row, col)->getColor();
                                if (p1[row][col] != t) {
                                    p1[row][col] = t;
                                    xw->fillRectangle(width - b_width - space + (col * blk_length),
                                                      85 + (row * blk_length), blk, blk, t);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}






