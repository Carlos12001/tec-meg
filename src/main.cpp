#include <iostream>
#include "connection.h"
class InitProgram{
public:
    static void start(){
        return;
    }
    static void testServerConnection(){
        auto serverConnection = new ServerConnection;
        serverConnection->initConnection();
        cout << serverConnection->getMessage() << endl;
        serverConnection->sendMessage("I got your message");
        delete serverConnection;
        return;
    };

};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
