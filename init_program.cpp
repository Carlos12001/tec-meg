//
// Created by carlo on 4/15/22.
//
#include "init_program.h"
#include <iostream>
#include "connection.h"
#include "mainwindow.h"
#include "utilities.h"
#include <QApplication>
#include "game.h"
using namespace std;
#include <nlohmann/json.hpp>
using json = nlohmann::json;

[[maybe_unused]]  void InitProgram::start() {
    return;
}

[[maybe_unused]] void InitProgram::testConnection() {
    cout << "Welcome to testConnection" << endl;
    cout << " \"0\" for server or any number for client" << endl;
    int inputNumber = Utilities::inputStringToInt();
    if (inputNumber == 0) {
        cout << "Test Server" << endl;
        InitProgram::testServerConnection();
    } else {
        cout << "Test Client" << endl;
        InitProgram::testClientConnection();
    }
}

[[maybe_unused]]  void InitProgram::testServerConnection() {
    auto connection = new ServerConnection;

    cout << "Please enter a number for the port: " << endl;
    int number =  Utilities::inputStringToInt();
    connection->setPortNumber(number);

    connection->initConnection();

    cout << connection-> getMessage() << endl;

    connection->sendMessage("Hi, by the server.");

    delete connection;
    return;
}

[[maybe_unused]]  void InitProgram::testClientConnection(){
    auto connection = new ClientConnection;

    cout << "Please enter a number for the port: " << endl;
    int number =  Utilities::inputStringToInt();
    connection->setPortNumber(number);


    connection->initConnection();

    connection->sendMessage("Hi!!, I'm the NEW client.");

    cout << connection->getMessage() << endl;

    delete connection;
    return;
}

[[maybe_unused]]  int InitProgram::initGUITest(int argc, char *argv[]){
    QApplication app =  QApplication(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}

[[maybe_unused]]  void InitProgram::matrixMemoryTest1(){
    auto matrix = MatrixMemory(42);
}

[[maybe_unused]] void InitProgram::matrixMemoryTest2(){
    auto matrix = MatrixMemory(20);
    matrix.getCard(0,0);
    matrix.getCard(8, 1);
    matrix.getMemoryState();
}

[[maybe_unused]]  void InitProgram::testClientReceiveInformation(){
    ClientConnection* connection = new ClientConnection();
    connection->initConnection();
    string data = connection->getMessage();
    json jsonNumOfCards;
    jsonNumOfCards = json::parse(data);
    int numOfCards = jsonNumOfCards["numOfCards"];
    cout << "The number of cards is: " << numOfCards << endl;
    return;
}