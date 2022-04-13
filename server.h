//
// Created by carlo on 4/13/22.
//

#ifndef TEC_MEG_SERVER_H
#define TEC_MEG_SERVER_H
#include "iostream"
#include "string.h"
using namespace std;
#include "connection.h"
#include "game.h"
#include "list"
#include "hash_map"

class InformationMessage{
public:
    string getInfo();
    void setInfo(const InformationMessage);
};

class MatrixMemory{
private:
    hash<string> ram;
    list<Card> disk;
    Card replaceCard();

public:
    Card getCard(int, int);
    string getMemoryState();
};

class Server{
private:
    Game game;
    ServerConnection connection;
    MatrixMemory memory;
public:
    void updateState();
    void initGame();
}


#endif //TEC_MEG_SERVER_H
