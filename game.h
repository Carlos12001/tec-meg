//
// Created by carlo on 4/13/22.
//

#ifndef TEC_MEG_GAME_H
#define TEC_MEG_GAME_H
#include "iostream"
#include "string.h"
using namespace std;

class Player{
public:
    string name;
    int points;
    bool myTurn = false;
};

class Card{
public:
    string id;
    int positionI;
    int positionJ;
    string image;
};

class Game {

};


#endif //TEC_MEG_GAME_H
