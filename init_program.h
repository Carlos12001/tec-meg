/**
 * @author Carlos12001
 * @brief This file has the class to start the program and the tests that have been done in the code.
 */

#ifndef TEC_MEG_INIT_PROGRAM_H
#define TEC_MEG_INIT_PROGRAM_H
#include "init_program.h"
#include <iostream>
#include "connection.h"
#include "mainwindow.h"
#include "utilities.h"
#include <QApplication>
#include "server.h"
#include "game.h"
using namespace std;

/**
 * @brief Start the program. It takes care of starting either the client or the server
 */
class InitProgram {
public:
    /**
     * @brief The method launcher the program. This program receives the necessary inputs to start the client or the server.
     * @param argc Number of arguments when starting the program.
     * @param argv The arguments when starting the program.
     * @return Status of the program if it was executed successfully.
     */
    static int start(int argc, char *argv[]);

};

/**
 * @brief Test the methods. It performs tests on the client GUI, the connection and the memory array.
 */
class TesterClass{
public:

    /**
     * @brief Receives user input and executes the client or server. It first waits for the type of connection and then asks for the port.
     */
    [[maybe_unused]] static void testConnection();

    /**
     * @brief Test the server connection. This performs a test of sending a message.
     */
    [[maybe_unused]]  static void testServerConnection();

    /**
     * @brief Test the client connection. This performs a test of sending a message.
     */
    [[maybe_unused]]  static void testClientConnection();

    /**
     * @brief Run the client interface. This method is deprecated since it works.
     * @param argc Number of arguments when starting the program.
     * @param argv The arguments when starting the program.
     * @return Status of the program if it was executed successfully.
     */
    [[maybe_unused]] static int initGUITest(int argc, char *argv[]);

    /**
     * @brief Performs the start-of-array test. This initializes the array to check if it manages to save the info in the json.
     */
    [[maybe_unused]] static void matrixMemoryTest1();

    /**
     * @brief Take the test obtaining a letter from the matrix. Request the info of the letter that is in memory and another that is not.
     */
    [[maybe_unused]] static void matrixMemoryTest2();

    /**
     * @brief Performs a test of receiving and sending info in json format. This test is performed on the client receiving the message and the server sending the information.
     */
    [[maybe_unused]] static void testReceiveInformation();

    /**
     * @brief Check if the client is able to receive the information in json. It reads the information from the server and transforms it into json.
     */
    [[maybe_unused]] static void testClientReceiveInformation();

    /**
     * @brief Check if the client is able to send the information in json. Send the information to the client.
     */
    [[maybe_unused]] static void testServerSendsInformation();

};

#endif //TEC_MEG_INIT_PROGRAM_H
