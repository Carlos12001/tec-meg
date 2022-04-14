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
    static void start() {
        return;
    }

    static void testConnection() {
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

    static void testServerConnection() {
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

    static void testClientConnection(){
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

    static int initGUITest(int argc, char *argv[]){
        QApplication app =  QApplication(argc, argv);
        MainWindow w;
        w.show();
        return app.exec();
    }

    static void matrixMemoryTest1(){
        auto matrix = MatrixMemory(42);
    };
};

int main(int argc, char *argv[]){
    InitProgram::matrixMemoryTest1();
    return 0;
}
