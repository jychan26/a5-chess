//
//  gameplayer.cpp
//  chess
//
//  Created by Jingtong Hu on 2020-04-11.
//  Copyright © 2020 CS246Team. All rights reserved.
//

#include "gameplayer.h"


GamePlayer::GamePlayer(Colour colour): colour(colour), score(0), player(nullptr) {}
void GamePlayer::setPlayer(string playerName, Board *board) {
    if (player) delete player;
    if (playerName == "human") {
        player = new Human;
    } else if (playerName == "computer[1]") {
        player = new Level1(colour, board);
    } else if (playerName == "computer[2]") {
        player = new Level2(colour, board);
    } else if (playerName == "computer[3]") {
        player = new Level3(colour, board);
    } else if (playerName == "computer[4]") {
        player = new Level4(colour, board);
    } else {
        player = nullptr;
    }
}
Move GamePlayer::nextMove() {
    if (player) return player->nextMove();
    Move move;
    return move;
}
GamePlayer::~GamePlayer() {
    delete player;
}

float GamePlayer::getScore() {return score;}
Colour GamePlayer::getColour() {return colour;}
bool GamePlayer::win(Colour colour) {
    if (colour == this->colour) {
        score += 1;
        return true;
    }
    return false;
}
void GamePlayer::stalemate() {score += 0.5;}

char GamePlayer::getPromotion() {return player->getPromotion();}

bool GamePlayer::isValid() {
    if (player == nullptr) return false;
    return true;
}
