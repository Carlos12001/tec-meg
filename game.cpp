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

MatrixMemory::MatrixMemory(int numberCards) : sizeJ (numberCards / 10){
    initMatrix();
}

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

    mixCards(images);
    firstSaveInDisk(images, allCards);

}

template<class T> void MatrixMemory::mixCards(list<T> &listTemp) {
    mt19937 gen( chrono::system_clock::now().time_since_epoch().count() );
    vector<T> V(listTemp.begin(), listTemp.end() );
    shuffle( V.begin(), V.end(), gen );
    listTemp.assign(V.begin(), V.end() );
}

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
                            {"used", tmp.used}});
        card++;
        imageSrc++;
    }
    ofstream file("data.json");
    file << std::setw(4) << dataDisk << std::endl;
    file.close();
}
