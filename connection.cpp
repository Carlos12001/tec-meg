//

#include "connection.h"


Connection::Connection(TypeConnection type) : type(type) {}

void Connection::error(const string& message) {
    perror(message.c_str());
}

Connection::~Connection() {
    close( socketOutput);
}

void Connection::setPortNumber(const int number) {
     portNumber = number;
}

ServerConnection::ServerConnection() : Connection(TypeConnection::SERVER) {}

void ServerConnection::initConnection() {
    if( inited) {
         error("The socket was previous initialed");
        return;
    }

    socketOutput = socket(AF_INET, SOCK_STREAM, 0);
    if (socketOutput < 0)
        error("ERROR opening socket");
    bzero((char *) &serverAddress, sizeof(serverAddress));


    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(portNumber);
    if (bind(socketOutput, (struct sockaddr *) &serverAddress,
             sizeof(serverAddress)) < 0)
        error("ERROR on binding");


    cout << "Information: The server connection is waiting the client." << endl;
    listen(socketOutput,5);

    clientAddressSize = sizeof(clientAddress);
    newSocketOutput = accept(socketOutput,
                             (struct sockaddr *) &clientAddress,
                             &clientAddressSize);

    if ( newSocketOutput < 0) {
        error("ERROR on accept");
    }else{
        cout << "Information: The connection was successful.\n" <<
             "-----------------\n" << endl;
         inited = true;
    }
    return;
}

string ServerConnection::getMessage() {
    int n = 256;
    char buffer[n];
    bzero(buffer,n);
    numberCharactersIO = read(newSocketOutput, buffer, n-1);
    if (numberCharactersIO < 0) error("ERROR reading from socket");
    cout << "Here is the message: " << buffer << endl;
    return "Message Complete";
}

void ServerConnection::sendMessage(string message) {
    int n = 256;
    char buffer[n];
    bzero(buffer,n);
    numberCharactersIO = write(newSocketOutput, "I got your message", 18);
    if (numberCharactersIO < 0) error("ERROR writing to socket");
    return;
}

ServerConnection::~ServerConnection() {
    close( newSocketOutput);
}

ClientConnection::ClientConnection() : Connection(TypeConnection::CLIENT) {
}

void ClientConnection::initConnection() {
    if( inited) {
         error("The socket was previous initialed");
        return;
    }

    socketOutput = socket(AF_INET, SOCK_STREAM, 0);
    if (socketOutput < 0)
        error("ERROR opening socket");
    serverHost = gethostbyname(ipHost);
    if (serverHost == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    bcopy((char *)serverHost->h_addr,
          (char *)&serverAddress.sin_addr.s_addr,
          serverHost->h_length);
    serverAddress.sin_port = htons(portNumber);

    if (connect(socketOutput, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
        error("ERROR connecting");
    else{
        cout << "Information: The connection was successful.\n" <<
        "-----------------\n" << endl;
        inited = true;
    }
    return;
}

string ClientConnection::getMessage() {
    int n = 256;
    char buffer[n];
    bzero(buffer,n);
    numberCharactersIO = read(socketOutput, buffer, 255);
    if (numberCharactersIO < 0)
        error("ERROR reading from socket");
    cout << "Here is the message: " << buffer << endl;
    return "Message Complete";
}

void ClientConnection::sendMessage(string message) {
    int n = message.length() + 1;
    char buffer[n];
    bzero(buffer,n);
    fgets(buffer,255,stdin);
    numberCharactersIO = write(socketOutput, buffer, strlen(buffer));
    if (numberCharactersIO < 0)
        error("ERROR writing to socket");
    return;
}
