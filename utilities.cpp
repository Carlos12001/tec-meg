#include "utilities.h"
#include "iostream"
using namespace std;

/**
     * @brief Recieve input from user and transform to int.
     * @return The input in int.
     */
int Utilities::inputStringToInt() {
    int inputNumber, errorCounter = 0;
    string inputString;
    while (true){
        try {
            cin >> inputString;
            inputNumber = stoi(inputString);
            break;
        }
        catch (...){
            cerr << "Your input is not a number. It was: " << inputString << endl;
            errorCounter++;
            if (errorCounter>=20) { cerr<<"Many tries!" << endl;exit(-1);}
        }
    }
    return inputNumber;
}