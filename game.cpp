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

    mixElementsList(images);
    firstSaveInDisk(images, allCards);
    initRam();
    getMemoryState();
}

template<class T> void MatrixMemory::mixElementsList(list<T> &listTemp) {
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
            bool used = dataDisk[i].at("used");
            foundCard = new Card;
            foundCard->id = id;
            foundCard->positionI = positionI;
            foundCard->positionJ = positionJ;
            foundCard->image = image;
            foundCard->used = used;
            break;
        }
    }
    if(foundCard==nullptr){
        cerr << "Error: No found card in the disk" << endl;
        exit(-1);
    }
    return foundCard;
}

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

string MatrixMemory::getMemoryState() {
    string result;
    cout << "The state of the ram is: " << endl;
    for (const auto& [key, value] : ram) {
        std::cout << '[' << key << "] = " << value->image << "; " << endl;
        result += string("[") + key + string("] = ") + value->image + string("; ");
    }
    return result;
}

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
    }
    resultCard = iterator->second;
    return resultCard;
}

Card *MatrixMemory::getCard(int positionI, int positionJ) {
    return getCard(string("cardI") + to_string(positionI) + string("J") + to_string(positionJ));
}
