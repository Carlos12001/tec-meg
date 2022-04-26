//
// Created by carlo on 4/25/22.
//

#include <gtest/gtest.h>
#include "game.h"
#include "connection.h"
#include <iostream>
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
    bool works = true;
    try {
        auto connection = new ServerConnection;
        int number = 8080;
        connection->setPortNumber(number);

        string message = connection->getMessage();

        connection->sendMessage("Hi, by the server.");
        delete connection;

        EXPECT_EQ("Hi!!, I'm the NEW client.", message);
    }
    catch (...){
        works = false;
    }
    EXPECT_TRUE(works);
}

/**
    * @brief Performs the start-of-array test. This initializes the array to check if it manages to save the info in the json.
*/
TEST(TestMatrixMemory, AddCards){
    bool works = true;
    try {
        auto matrix = MatrixMemory(42);
        string state = matrix.getMemoryState();
    }
    catch(...){
        works = false;
    }
    EXPECT_TRUE(works);
}

/**
    * @brief Take the test obtaining a letter from the matrix. Request the info of the letter that is in memory and another that is not.
*/
TEST(TestMatrixMemory, GetCards){


    bool works = true;
    try {
        auto matrix = MatrixMemory(20);
        auto card00 = matrix.getCard(0,0);
        auto card81 = matrix.getCard(8, 1);
        string state = matrix.getMemoryState();
        EXPECT_NE(card00, card81);
    }
    catch(...){
        works = false;
    }
    EXPECT_TRUE(works);


}

/**
    * @brief Check if the client is able to receive the information in json. It reads the information from the server and transforms it into json.
*/
TEST(TestClient, ReceiveInformation){
    string data = "{\"numOfCards\":60}";
    json jsonNumOfCards;
    jsonNumOfCards = json::parse(data);
    int numOfCards = jsonNumOfCards["numOfCards"];


    EXPECT_EQ(numOfCards, 60);
}

/**
     * @brief Check if the client is able to send the information in json. Send the information to the client.
     */
TEST(TestServer,SendsInformation){
    json jsonNumOfCards;
    jsonNumOfCards = {{"numOfCards", 60}};
    string expect  = "{\n"
                     "    \"numOfCards\": 60\n"
                     "}";
    string output = jsonNumOfCards.dump(4);

    EXPECT_EQ(expect, output);
}