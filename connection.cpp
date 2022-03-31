//
// Created by carlo on 3/27/22.
//

//Default include.
#include "connection.h"
#include "iostream"
#include <cstring>
using namespace std;
//Includes for the client and server connection.
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
//Include for the client.
//#include <netdb.h>


Connection::Connection(TypeConnection type) : type(type) {}

void Connection::error(const string& message) {
    perror(message.c_str());
}

Connection::~Connection() {
    close(this->socketOutput);
};

ServerConnection::ServerConnection() : Connection(TypeConnection::SERVER) {}

void ServerConnection::initConnection() {
//    Check is the was inited before.
    if(this->inited) {
        this->error("The socket was previous initialed");
        return;
    }

//    Create the socket.
    this->socketOutput = socket(AF_INET, SOCK_STREAM, 0);
//    Check is the socket was open successful.
    if(this->socketOutput<0) {
        this->error("ERROR opening socket");
        return;
    }
//    Set buffer of the serverAddress in 0.
    bzero((char *)&this->serverAddress, sizeof(this->serverAddress));
//    Set the values of the serverAddress.
    (this->serverAddress).sin_family = AF_INET;
    (this->serverAddress).sin_addr.s_addr = INADDR_ANY;
    (this->serverAddress).sin_port = htons(this->portNumber);
//    Bind the socket to address.
//    For a server socket on the Internet,
//    an address consists of a port number on the host machine.
    while (true){
        int bindOutput = bind(this->socketOutput, (struct sockaddr *) &(this->serverAddress),
                              sizeof(this->serverAddress));
        if ( bindOutput < 0) {
            this->portNumber++;
            this->error(string("ERROR on binding: new port set in: ")
                                + to_string(this->portNumber));
        }
        else if (9000 < portNumber){
            this->error("ERROR on binding: We try more 20 different ports");
            exit(1);
        }
        else{
            break;
        }
    }
//    Waiting the client.
    cout << "Information: The server connection is waiting the client." << endl;
    listen(socketOutput, 5);

    this->clientAddressSize = sizeof(this->clientAddress);
//    Accept the client.
    this->newSocketOutput = accept(this->socketOutput,
                             (struct sockaddr *) &(this->clientAddress),
                             &(this->clientAddressSize));
    if (this->newSocketOutput < 0) {
        error("ERROR on accept");
    }else{
        cout << "Information: The connection was successful." << endl;
        this->inited = true;
    }
    return;
}

string ServerConnection::getMessage() {
    //    Set buffer in 0.
    char buffer[256];
    bzero(buffer,256);
    this->numberCharactersIO = read(this->newSocketOutput,buffer, 255);
    if (numberCharactersIO < 0) {
        error("ERROR reading from socket");
    }
    return string(buffer);
}

void ServerConnection::sendMessage(string message) {
    //    Set buffer in 0.
    char buffer[256];
    bzero(buffer,256);
    this->numberCharactersIO = write(this->newSocketOutput,"I got your message",18);
    if (this->numberCharactersIO < 0) {
        error("ERROR writing to socket");
    }
    return;
}

ServerConnection::~ServerConnection() {
    close(this->newSocketOutput);
}

ClientConnection::ClientConnection() : Connection(TypeConnection::CLIENT) {
    this->setIpHost("localhost");
}

void ClientConnection::initConnection() {
    //    Check is the was inited before.
    if(this->inited) {
        this->error("The socket was previous initialed");
        return;
    }

//    Create the socket.
    this->socketOutput = socket(AF_INET, SOCK_STREAM, 0);
//    Check is the socket was open successful.
    if (this->socketOutput < 0)
        error("ERROR opening socket");
    this->serverHost = gethostbyname(this->ipHost);
    if (this->serverHost == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &(this->serverAddress), sizeof(this->serverAddress));

    (this->serverAddress).sin_family = AF_INET;

    bcopy((char *)(this->serverHost)->h_addr,
          (char *)&(this->serverAddress).sin_addr.s_addr,
          (this->serverHost)->h_length);

    (this->serverAddress).sin_port = htons(this->portNumber);

    if (connect((this->socketOutput),(struct sockaddr *) &(this->serverAddress),
            sizeof(this->serverAddress)) < 0)
        error("ERROR connecting");

    return;
}

string ClientConnection::getMessage() {
    //    Set buffer in 0.
    char buffer[256];
    bzero(buffer,256);
    numberCharactersIO = read(socketOutput,buffer,255);
    if (numberCharactersIO < 0)
        error("ERROR reading from socket");
    printf("%s\n",buffer);
    return string (buffer);
}

void ClientConnection::sendMessage(string message) {
    //    Set buffer in 0.
    char buffer[256];
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    numberCharactersIO = write(socketOutput,buffer,strlen(buffer));
    if (numberCharactersIO < 0)
        error("ERROR writing to socket");
    return;
}

void ClientConnection::setPortNumber(const int portNumber) {
    this->portNumber = portNumber;
}

void ClientConnection::setIpHost(const string ipString) {
    this->ipHost = const_cast<char *>(ipString.c_str());
}
