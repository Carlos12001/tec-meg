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


class Server{
private:
    Game game;
    ServerConnection connection;

public:
    void updateState();
    void initGame();
};


#endif //TEC_MEG_SERVER_H
