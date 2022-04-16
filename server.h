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

/**
 * @brief The server of game. Store all the information the game and excuete all the methods to have the game updated.
 */
class Server{
private:

    /**
     * @brief The memory of the game of the cards.
     */
    MatrixMemory* matrixMemory = nullptr;

    /**
     * @brief The information of the game.
     */
    Game* game = nullptr;

    /**
     * @brief The connection with the client.
     */
    ServerConnection* connection = nullptr;

public:

    /**
     * @brief Update State od the game.
     */
    void updateState();

    /**
     * @brief Init the game. Create the matrix memory, connection and game information.
     * @param numberOfCards The number of Cards.
     * @param numberPort The number of the port.
     */
    void initGame(int numberOfCards, int numberPort);

    /**
     * @brief Send basic informaction to client. The client need this information to init.
     * @param numberOfCards The number of Cards.
     */
    void sendBasicInformation(int numberOfCards);

    /**
     * @brief Receive the button image. This method receives the id about a card from the client need.
     * @return Returns the id the card needed.
     */
    string receiveCard();

    /**
     * @brief Send information from this letter. Send about the letter client need.
     * @param idCard The ID of the card.
     */
    void sendIdCard(string idCard);

};


#endif //TEC_MEG_SERVER_H
