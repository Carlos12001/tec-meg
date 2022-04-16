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

    MatrixMemory* matrixMemory = nullptr;

    Game* game = nullptr;

    ServerConnection* connection = nullptr;

public:

    void updateState();

    void initGame(int numberOfCards, int numberPort);

    void sendBasicInformation(int numberOfCards);

    string receiveCard();

    void sendIdCard(string idCard);

};


#endif //TEC_MEG_SERVER_H
