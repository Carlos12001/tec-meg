//
// Created by carlo on 4/13/22.
//

#include "game.h"
#include "json/json.h"

MatrixMemory::MatrixMemory(int numberCards) : sizeJ (numberCards % 10){
    initMatrix();
}

void MatrixMemory::initMatrix() {
    list<string> images;
    for(int i = 0; i < sizeI; i++){
        for (int j = 0; j < sizeJ; j++){
            Card newCard =  Card();
            newCard.positionI = i;
            newCard.positionJ = j;
            newCard.id = string("cardI") + to_string(i) + string("J") + to_string(j);
            images.push_back(to_string(i * 10) + to_string(j) + string(".png"));
        }
    }

    for (auto it = images.begin(); it != images.end(); ++it)
        cout << *it << endl;
}
