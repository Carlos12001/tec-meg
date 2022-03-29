//
// Created by carlo on 3/27/22.
//
#ifndef TEC_MEG_CONNECTION_H
#define TEC_MEG_CONNECTION_H
//Default include.
#include "iostream"
#include <cstring>
using namespace std;
//Includes for the client and server connection.
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
//Include for the client.
#include <netdb.h>




enum TypeConnection{
    SERVER, CLIENT
};

class Connection {
protected:

    const TypeConnection type;

    bool inited = false;

    int socketOutput{};

    int portNumber{};

    int numberCharactersIO{};

    char buffer [256]{};

    sockaddr_in serverAddress{};

    static void error(const string& message);
public:

    Connection(TypeConnection type);

    virtual void initConnection() = 0;

    virtual string getMessage() = 0;

    virtual void sendMessage(string message) = 0;

    virtual ~Connection();
};

class ServerConnection: public Connection{
protected:

    int newSocketOutput = -1;

    socklen_t clientAddressSize;

    sockaddr_in clientAddress;
public:

    ServerConnection();

    void initConnection() override;

    string getMessage() override;

    void sendMessage(string message) override;

    ~ServerConnection();
};

class ClientConnection: public Connection{
protected:

    hostent* serverHost = nullptr;
public:
    ClientConnection();

    void initConnection() override;

    string getMessage() override;

    void sendMessage(string message) override;
};


#endif //TEC_MEG_CONNECTION_H
