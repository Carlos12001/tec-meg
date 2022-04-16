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
/**
 * @brief The data of Player.
 */
class Player{
public:
    /**
     * @brief Name of player.
     */
    string name;

    /**
     * @brief Points of the player.
     */
    int points;

};

/**
 * @brief The model of the object Card.
 */
class Card{
public:
    /**
     * @brief The ID of the card.
     */
    string id;

    /**
     * @brief The position i in the matrix.
     */
    int positionI;

    /**
     * @brief The position j in the matrix.
     */
    int positionJ;

    /**
     * @brief The image of the card.
     */
    string image;

    /**
     * @brief Say if the card was in the ram.
     */
    bool inMemory = false;
};

/**
 * @brief The matrix of the game. This matrix stores the data of all the cards.
 */
class MatrixMemory{
private:

    /**
     * @brief Size max in i.
     */
    const int sizeI = 10;

    /**
     * @brief Size max in j.
     */
    const int sizeJ;

    /**
     * @brief Store the cards in memory with a quick accesses.
     */
    map <string, Card*> ram;

    /**
     * @brief Mix the element of a list. The recibe a list and mix its elements.
     * @tparam T Type of elements in the list.
     * @param listTemp The list to mix.
     */
    template <class T > void mixElementsList(list<T> &listTemp );

    /**
     * @brief Initalize the matrix. Create the cards and their images store in disk and 30% in ram.
     */
    void initMatrix();

    /**
     * @brief Save all the cards in disk.
     * @param images The list of all images.
     * @param allCards The list of all cards.
     */
    void firstSaveInDisk(list<string>& images, list<Card>& allCards);

    /**
     * @brief Choose a card to replace. This is the algorithm to choose the page to replacd.
     * @return The card choosed.
     */
    Card* replaceCard();

    /**
     * @brief This search the card in the file json. Do the search in file and when find the card charge it in the program.
     * @return The card searched.
     */
    Card* getCardFromDisk(string id);

    /**
     * @brief Initalize the ram. Set firts 30% of the cards in memory.
     */
    void initRam();

public:

    /**
     * @brief The constructor of the class.
     * @param numberCards Receive the number of cards to create.
     */
    MatrixMemory(int numberCards);

    /**
     * * @brief This is like a MMU. This MMU search the card in ram, and is not there do a page fault and searched in disk.
     * @param id The ID of the card to search.
     * @return The card searched.
     */
    Card* getCard(string id);

    /**
    * * @brief Call getCard(string id). Is to use that method without the id.
    * @param id The ID of the card to search.
    * @return The card searched.
    */
    Card* getCard(int positionI, int positionJ);

    /**
     * @brief Prints in console the state of ram.
     * @return Return the state.
     */
    string getMemoryState();

};

/**
 * @brief Store data about the game and players. This class does what action do the game.
 */
class Game {
public:

    /**
     * @brief Store the 2 players.
     */
    Player* players[2];

    /**
     * @brief The constructor of the game.
     */
    Game();

    /**
     * @brief Update the state of the game.
     * @param pointP1 The points of the player 1.
     * @param pointsP2 The points of the player 2.
     */
    void updateGame(int pointP1, int pointsP2);
};

#endif //TEC_MEG_GAME_H
