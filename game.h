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


class MatrixMemory{
private:
    map <string, Card*> ram;
    template <class T > void mixElementsList(list<T> &listTemp );
    void initMatrix();
    void firstSaveInDisk(list<string>& images, list<Card>& allCards);
    Card* replaceCard();
    Card* getCard(string id);
    Card* getCardFromDisk(string id);
    void initRam();

public:
    const int sizeI = 10;
    const int sizeJ;
    MatrixMemory(int numberCards);
    Card* getCard(int positionI, int positionJ);
    string getMemoryState();
};


class Game {
public:
    Player players[2];
    void initGame();
};


#endif //TEC_MEG_GAME_H
