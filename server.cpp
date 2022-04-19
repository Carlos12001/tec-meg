//
// Created by carlo on 4/13/22.
//

#include "server.h"
#include "math.h"
#include <nlohmann/json.hpp>
#include "iostream"
using namespace std;
using json = nlohmann::json;

/**
     * @brief Update State od the game.
     */
void Server::updateState() {
    while(true){
        string idCard = receiveCard();
        if("FINISH"==idCard)
            break;
        else if ("None"==idCard){
            cout << "\n----------Game State----------\n";
            cout << "Player 1 Points: " << game->players[0]->points << endl;
            cout << "Player 2 Points: " << game->players[1]->points << endl;
//            matrixMemory->refreshRam();
            matrixMemory->getMemoryState();
        }
        else{
            sendIdCard(idCard);
        }
    }
    cout << "\n\n\n--------------------" << "The final state of the ram is: " << "--------------------" << endl;
    matrixMemory->getMemoryState();
    exit(0);
}

/**
     * @brief Init the game. Create the matrix memory, connection and game information.
     * @param numberOfCards The number of Cards.
     * @param numberPort The number of the port.
     */
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

    updateState();
}

/**
     * @brief Send information from this letter. Send about the letter client need.
     * @param idCard The ID of the card.
     */
void Server::sendIdCard(string idCard) {
    Card* cardToSend = matrixMemory->getCard(idCard);
    string stringCardSend;
    json jsonCard = {{"id", cardToSend->id},
                     {"positionI", cardToSend->positionI},
                     {"positionJ", cardToSend->positionJ},
                     {"image", cardToSend->image},
                     {"inMemory", cardToSend->inMemory}};
    stringCardSend = jsonCard.dump(4);
    connection->sendMessage(stringCardSend);
}

/**
     * @brief Send basic informaction to client. The client need this information to init.
     * @param numberOfCards The number of Cards.
     */
void Server::sendBasicInformation(int numberOfCards) {
    json jsonNumOfCards;
    jsonNumOfCards = {{"numOfCards", numberOfCards}};
    connection->sendMessage(jsonNumOfCards.dump(4));
    return;
}

/**
     * @brief Receive the button image. This method receives the id about a card from the client need.
     * @return Returns the id the card needed.
     */
string Server::receiveCard() {
    string data = connection->getMessage();
    json jsonIDCard;
    jsonIDCard = json::parse(data);
    string idCard = jsonIDCard["id"];
    if ("None"==idCard){
        int p1 = jsonIDCard["playerPoints1"];
        int p2 = jsonIDCard["playerPoints2"];
        game->updateGame(p1*100,p2*100);
    }
    return idCard;
}