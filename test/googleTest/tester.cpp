//
// Created by carlo on 4/25/22.
//

#include <gtest/gtest.h>
#include "../../init_program.h"
#include <iostream>
#include "QApplication"
#include "nlohmann/json.hpp"
using namespace std;
using json = nlohmann::json;

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

/**
    * @brief Test the server connection. This performs a test of sending a message.
*/
TEST(TestConnection, ServerRecieve) {
    auto connection = new ServerConnection;

    int number =  8080;
    connection->initConnection();

    string message  =  connection-> getMessage();

    connection->sendMessage("Hi, by the server.");
    delete connection;

    //    EXPECT_STREQ("Hi!!, I'm the NEW client.", message)
}

/**
    * @brief Test the client connection. This performs a test of sending a message.
*/
TEST(TestConnection, ClientRecieve){
    auto connection = new ClientConnection;
    int number =  8080;
    connection->setPortNumber(number);
    connection->initConnection();

    connection->sendMessage("Hi!!, I'm the NEW client.");

    string message = connection->getMessage();

    delete connection;
    //    EXPECT_STREQ("Hi, by the server.", message)
}

/**
    * @brief Performs the start-of-array test. This initializes the array to check if it manages to save the info in the json.
*/
TEST(TestMatrixMemory, AddCards){
    auto matrix = MatrixMemory(42);
    string state  = matrix.getMemoryState();

    //    EXPECT_STREQ("{{\"numOfCards\", 60}}", jsonNumOfCards.dump(4))
}

/**
    * @brief Take the test obtaining a letter from the matrix. Request the info of the letter that is in memory and another that is not.
*/
TEST(TestMatrixMemory, GetCards){
    auto matrix = MatrixMemory(20);
    auto card00 = matrix.getCard(0,0);
    auto card81 = matrix.getCard(8, 1);
    string state  = matrix.getMemoryState();

    //    EXPECT_STREQ("{{\"numOfCards\", 60}}", state)
    EXPECT_NE(card00, card81);
}

/**
    * @brief Check if the client is able to receive the information in json. It reads the information from the server and transforms it into json.
*/
TEST(TestClient, ReceiveInformation){
    auto connection = new ClientConnection;
    int number =  8080;
    connection->setPortNumber(number);
    connection->initConnection();


    string data = connection->getMessage();
    json jsonNumOfCards;
    jsonNumOfCards = json::parse(data);
    int numOfCards = jsonNumOfCards["numOfCards"];


    //    EXPECT_STREQ("{{\"numOfCards\", 60}}", data)
    EXPECT_EQ(numOfCards, 60);
}

/**
     * @brief Check if the client is able to send the information in json. Send the information to the client.
     */
TEST(TestServer,SendsInformation){

    json jsonNumOfCards;
    jsonNumOfCards = {{"numOfCards", 60}};

//    EXPECT_STREQ("{{\"numOfCards\", 60}}", jsonNumOfCards.dump(4))
}