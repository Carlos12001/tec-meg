//
// Created by carlo on 4/13/22.
//

#include "game.h"
#include <chrono>
#include <random>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>
#include "list"
#include <fstream>
using json = nlohmann::json;

/**
    * @brief The constructor of the class.
    * @param numberCards Receive the number of cards to create.
    */
MatrixMemory::MatrixMemory(int numberCards) : sizeJ (numberCards / 10){
    initMatrix();
}

/**
     * @brief Initalize the matrix. Create the cards and their images store in disk and 30% in ram.
     */
void MatrixMemory::initMatrix() {
    list<string> images;
    list<Card> allCards;
    int counter = 0;
    for(int i = 0; i < sizeI; i++){
        for (int j = 0; j < sizeJ; j++){
            Card newCard = Card();
            newCard.positionI = i;
            newCard.positionJ = j;
            newCard.id = string("cardI") + to_string(i) + string("J") + to_string(j);
            allCards.push_back(newCard);
            images.push_back( to_string(counter/2) + string(".png"));
            counter ++;
        }
    }

    mixElementsList(images);
    firstSaveInDisk(images, allCards);
    initRam();
    getMemoryState();
}

/**
     * @brief Mix the element of a list. The recibe a list and mix its elements.
     * @tparam T Type of elements in the list.
     * @param listTemp The list to mix.
     */
template<class T> void MatrixMemory::mixElementsList(list<T> &listTemp) {
    mt19937 gen( chrono::system_clock::now().time_since_epoch().count() );
    vector<T> V(listTemp.begin(), listTemp.end() );
    shuffle( V.begin(), V.end(), gen );
    listTemp.assign(V.begin(), V.end() );
}

/**
     * @brief Save all the cards in disk.
     * @param images The list of all images.
     * @param allCards The list of all cards.
     */
void MatrixMemory::firstSaveInDisk(list<string>& images, list<Card>& allCards) {
    json dataDisk;
    _List_const_iterator<Card> card = allCards.begin();
    _List_const_iterator<string> imageSrc =  images.begin();
    for (int i = 0; i < sizeJ*sizeI ; ++i) {
        Card tmp =  *card;
        tmp.image = *imageSrc;
        dataDisk.push_back({{"id", tmp.id},
                            {"positionI", tmp.positionI},
                            {"positionJ", tmp.positionJ},
                            {"image", tmp.image},
                            {"inMemory", tmp.inMemory}});
        card++;
        imageSrc++;
    }
    ofstream file("data.json");
    file << std::setw(4) << dataDisk << std::endl;
    file.close();
}

/**
     * @brief This search the card in the file json. Do the search in file and when find the card charge it in the program.
     * @return The card searched.
     */
Card* MatrixMemory::getCardFromDisk(string id) {
    ifstream file("data.json", std::ifstream::in);
    json dataDisk;
    file >> dataDisk;
    file.close();
    Card* foundCard = nullptr;
    for (int i = 0; i < sizeJ*sizeI; ++i) {
        string idIterator = dataDisk[i].at("id");
        if(id == idIterator){
            int positionI = dataDisk[i].at("positionI");
            int positionJ = dataDisk[i].at("positionJ");
            string image = dataDisk[i].at("image");
            bool inMemory = dataDisk[i].at("inMemory");
            foundCard = new Card;
            foundCard->id = id;
            foundCard->positionI = positionI;
            foundCard->positionJ = positionJ;
            foundCard->image = image;
            foundCard->inMemory = inMemory;
            break;
        }
    }
    if(foundCard==nullptr){
        cerr << "Error: No found card in the disk" << endl;
        exit(-1);
    }
    return foundCard;
}

/**
     * @brief Initalize the ram. Set firts 30% of the cards in memory.
     */
void MatrixMemory::initRam() {
    int counter = 0;
    for (int i = 0; i < sizeI ; ++i) {
        for (int j = 0; j < sizeJ ; ++j) {
            if(sizeJ*sizeI*0.3<=counter) break;
            else counter++;
            string id = string("cardI") + to_string(i) + string("J") + to_string(j);
            auto card = getCardFromDisk(id);
            ram[id] = card;
        }
    }
}

/**
     * @brief Prints in console the state of ram.
     * @return Return the state.
     */
string MatrixMemory::getMemoryState() {
    string result;
    cout << "The state of the ram is: " << endl;
    for (const auto& [key, value] : ram) {
        std::cout << '[' << key << "] = " << value->image << "; " << endl;
        result += string("[") + key + string("] = ") + value->image + string("; ");
    }
    return result;
}

/**
     * @brief Choose a card to replace. This is the algorithm to choose the page to replacd.
     * @return The card choosed.
     */
Card* MatrixMemory::replaceCard() {
    Card* resultCard = nullptr;
    list<string> idCards;
    for (const auto& [key, value] : ram) {
        idCards.push_back(key);
    }
    mixElementsList(idCards);
    auto iteratorList = idCards.begin();
    auto iteratorRam = ram.find(*iteratorList);
    resultCard = iteratorRam->second;
    return resultCard;
}

/**
     * * @brief This is like a MMU. This MMU search the card in ram, and is not there do a page fault and searched in disk.
     * @param id The ID of the card to search.
     * @return The card searched.
     */
Card* MatrixMemory::getCard(string id) {
    Card* resultCard = nullptr;
    auto iterator = ram.find(id);
    if (  iterator == ram.end() ) {
        cout << endl << "--------------" << "PAGE FAULT" <<  "--------------" << endl;
        cout<<"Element \"" << id << "\" not found" << endl;

        auto deleteCard = replaceCard();
        auto replacementCard = getCardFromDisk(id);

        iterator = ram.find(deleteCard->id);
        delete iterator->second;
        ram.erase(iterator);

        ram[id] = replacementCard;
        iterator = ram.find(id);
        iterator->second->inMemory = true;
        getMemoryState();
    }
    resultCard = iterator->second;
    resultCard->inMemory = !(resultCard->inMemory);
    return resultCard;
}

/**
    * * @brief Call getCard(string id). Is to use that method without the id.
    * @param id The ID of the card to search.
    * @return The card searched.
    */
Card *MatrixMemory::getCard(int positionI, int positionJ) {
    return getCard(string("cardI") + to_string(positionI) + string("J") + to_string(positionJ));
}

/**
     * @brief The constructor of the game.
     */
Game::Game(){
    Player* player1 = new Player;
    player1->name = "Player 1";
    Player* player2 = new Player;
    player2->name = "Player 2";
    players[0]= player1;
    players[1] = player2;
}

/**
     * @brief Update the state of the game.
     * @param pointP1 The points of the player 1.
     * @param pointsP2 The points of the player 2.
     */
void Game::updateGame(int pointP1, int pointsP2) {
    players[0]->points=pointP1;
    players[1]->points=pointsP2;
}
