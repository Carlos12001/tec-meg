#include <iostream>
#include "connection.h"
#include "mainwindowclient.h"
#include <QApplication>

class InitProgram {
public:
    static void start() {
        return;
    }

    static void testConnection() {
        cout << "Welcome to testConnection" << endl;
        int input = 0;
        string a;
        cin >> a;
        input = stoi(a);
        if (input == 0) {
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
    InitProgram::testConnection();
}














class Card{
};

class MatrixMemory{
private:


/**
 *
 */
list<Card> ram;

/**
 *
 */
list<Card> disk;


void initMemory(int size){

}

/**
 *
 * @param positionI
 * @param positionJ
 * @return
 */
Card getCard(int positionI, int positionJ){

}
/**
 *
 * @param positionI
 * @param positionJ
 */
void replaceCard(int positionI, int positionJ){

}


};

















