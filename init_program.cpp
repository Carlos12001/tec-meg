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

/**
     * @brief The method launcher the program. This program receives the necessary inputs to start the client or the server.
     * @param argc Number of arguments when starting the program.
     * @param argv The arguments when starting the program.
     * @return Status of the program if it was executed successfully.
     */
int InitProgram::start(int argc, char *argv[]) {

    cout << "Welcome to testConnection" << endl;
    cout << " \"0\" for server or any number for client" << endl;
    int inputSelection = Utilities::inputStringToInt();

    cout << "Please enter a number for the port: " << endl;
    int numberPort =  Utilities::inputStringToInt();
    if (inputSelection == 0) {
        cout << "Server" << endl;
        cout << "Enter number of cards: " << endl;
        int numOfCards = Utilities::inputStringToInt();

        Server *server = new Server();
        server->initGame(numOfCards, numberPort);
        return 0;
    } else {
        cout << "Client" << endl;
        QApplication app =  QApplication(argc, argv);
        MainWindow w;
        w.initGame(numberPort);
        w.show();
        return app.exec();
    }
}

/**
     * @brief Receives user input and executes the client or server. It first waits for the type of connection and then asks for the port.
     */
[[maybe_unused]] void TesterClass::testConnection() {
    cout << "Welcome to testConnection" << endl;
    cout << " \"0\" for server or any number for client" << endl;
    int inputNumber = Utilities::inputStringToInt();
    if (inputNumber == 0) {
        cout << "Test Server" << endl;
        TesterClass::testServerConnection();
    } else {
        cout << "Test Client" << endl;
        TesterClass::testClientConnection();
    }
}

/**
     * @brief Test the server connection. This performs a test of sending a message.
     */
[[maybe_unused]]  void TesterClass::testServerConnection() {
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

/**
     * @brief Test the client connection. This performs a test of sending a message.
     */
[[maybe_unused]]  void TesterClass::testClientConnection(){
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

/**
     * @brief Run the client interface. This method is deprecated since it works.
     * @param argc Number of arguments when starting the program.
     * @param argv The arguments when starting the program.
     * @return Status of the program if it was executed successfully.
     */
[[maybe_unused]]  int TesterClass::initGUITest(int argc, char *argv[]){
    QApplication app =  QApplication(argc, argv);
    MainWindow w;
    cout << "Please enter a number for the port: " << endl;
    int number =  Utilities::inputStringToInt();
    w.initGame(number);
    w.show();
    return app.exec();
}

/**
     * @brief Performs the start-of-array test. This initializes the array to check if it manages to save the info in the json.
     */
[[maybe_unused]]  void TesterClass::matrixMemoryTest1(){
    auto matrix = MatrixMemory(42);
}

/**
 * @brief Take the test obtaining a letter from the matrix. Request the info of the letter that is in memory and another that is not.
 */
[[maybe_unused]] void TesterClass::matrixMemoryTest2(){
    auto matrix = MatrixMemory(20);
    matrix.getCard(0,0);
    matrix.getCard(8, 1);
    matrix.getMemoryState();
}

/**
     * @brief Performs a test of receiving and sending info in json format. This test is performed on the client receiving the message and the server sending the information.
     */
[[maybe_unused]] void TesterClass::testReceiveInformation() {
    cout << "Welcome to testConnection" << endl;
    cout << " \"0\" for server or any number for client" << endl;
    int inputNumber = Utilities::inputStringToInt();
    if (inputNumber == 0) {
        cout << "Test Server" << endl;
        TesterClass::testServerSendsInformation();
    } else {
        cout << "Test Client" << endl;
        TesterClass::testClientReceiveInformation();
    }
}

/**
     * @brief Check if the client is able to receive the information in json. It reads the information from the server and transforms it into json.
     */
[[maybe_unused]]  void TesterClass::testClientReceiveInformation(){
    auto connection = new ClientConnection;

    cout << "Please enter a number for the port: " << endl;
    int number =  Utilities::inputStringToInt();
    connection->setPortNumber(number);


    connection->initConnection();

    string data = connection->getMessage();
    json jsonNumOfCards;
    jsonNumOfCards = json::parse(data);
    int numOfCards = jsonNumOfCards["numOfCards"];
    cout << "The number of cards is: " << numOfCards << endl;
    return;
}

/**
     * @brief Check if the client is able to send the information in json. Send the information to the client.
     */
[[maybe_unused]]  void TesterClass::testServerSendsInformation(){
    auto connection = new ServerConnection;

    cout << "Please enter a number for the port: " << endl;
    int number =  Utilities::inputStringToInt();
    connection->setPortNumber(number);

    connection->initConnection();
    json jsonNumOfCards;
    jsonNumOfCards = {{"numOfCards", 60}};
    cout << "The json content is: \n" << jsonNumOfCards.dump(4) << endl;

    connection->sendMessage(jsonNumOfCards.dump(4));
    return;
}