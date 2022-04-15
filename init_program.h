//
// Created by carlo on 4/15/22.
//

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

class InitProgram {
public:
    [[maybe_unused]] static void start();

    [[maybe_unused]] static void testConnection();

    [[maybe_unused]]  static void testServerConnection();

    [[maybe_unused]]  static void testClientConnection();

    [[maybe_unused]] static int initGUITest(int argc, char *argv[]);

    [[maybe_unused]] static void matrixMemoryTest1();

    [[maybe_unused]] static void matrixMemoryTest2();

    [[maybe_unused]] static void testClientReceiveInformation();
};

#endif //TEC_MEG_INIT_PROGRAM_H
