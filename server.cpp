//
// Created by carlo on 4/13/22.
//

#include "server.h"
#include "math.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

void Server::updateState() {
    while(true){
        string idCard = receiveCard();
        if("FINISH")
            break;
        game->updateGame(0,0);
        sendIdCard(idCard);
    }
    cout << "\n--------------------" << "The final state of the ram is: " << "--------------------" << endl;
    matrixMemory->getMemoryState();
    exit(0);
}

void Server::initGame(int numberOfCards, int numberPort){
    connection = new ServerConnection;
    connection->setPortNumber(numberPort);
    connection->initConnection();


    if(100<numberOfCards)
        numberOfCards = 100;
    else if(numberOfCards < 10)
        numberOfCards = 10;
    else
        numberOfCards = roundf(numberOfCards * 0.1) / 0.1;

    matrixMemory = new MatrixMemory(numberOfCards);

    sendBasicInformation(numberOfCards);

    game = new Game();

//    updateState();
}

void sendIdCard(string idCard) {
}

void Server::sendBasicInformation(int numberOfCards) {
    json jsonNumOfCards;
    jsonNumOfCards = {{"numOfCards", numberOfCards}};
    connection->sendMessage(jsonNumOfCards.dump(4));
    return;
}

string Server::receiveCard() {
    return std::string();
}