//
// Created by carlo on 4/13/22.
//

#ifndef TEC_MEG_GAME_H
#define TEC_MEG_GAME_H
#include "iostream"
#include "string.h"
using namespace std;
#include "list"
#include "map"

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
    bool used = false;
};

class InformationMessage{
public:
    string getInfo();
    void setInfo(const InformationMessage);
};

class MatrixMemory{
private:
    map <string, Card> ram;
    Card replaceCard();
    void mixCards();
    void distributeCards();
    void initMatrix();

public:
    const int sizeI = 10;
    const int sizeJ;
    MatrixMemory(int numberCards);
    Card getCard(string id);
    string getMemoryState();
};


class Game {
public:
    Player players[2];
    MatrixMemory memory;
    void initGame();

};


#endif //TEC_MEG_GAME_H
