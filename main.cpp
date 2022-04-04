#include <iostream>
#include "connection.h"
#include "mainwindow.h"
#include "utilies.h"
#include <QApplication>
using namespace std;
class InitProgram {
public:
    static void start() {
        return;
    }

    static void testConnection() {
        cout << "Welcome to testConnection" << endl;
        cout << "0 for server or ay number for client" << endl;
        int inputNumber = Utilies::inputStringToInt();
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
        connection->initConnection();
        cout << connection->getMessage() << endl;
        connection->sendMessage("I got your message");
        delete connection;
        return;
    }
    static void testClientConnection(){
        auto connection = new ClientConnection;
        connection->sendMessage("I got your message");
        connection->initConnection();
        cout << connection->getMessage() << endl;
        delete connection;
        return;
    };

    static int initGUITest(int argc, char *argv[]){
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();

    }
};

int main(int argc, char *argv[]){
    InitProgram::initGUITest(argc, argv);
    return 0;
}
