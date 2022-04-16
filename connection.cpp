//

#include "connection.h"

/**
     *
     * @brief The constructor of the class.
     * @param type Decide the type of the connection.
     */
Connection::Connection(TypeConnection type) : type(type) {}

/**
     * @brief Print it was a an error.
     * @param message The message to print.
     */
void Connection::error(const string& message) {
    perror(message.c_str());
}

/**
     * @brief Close all the connections.
     */
Connection::~Connection() {
    close( socketOutput);
}

/**
     * @brief Set of the param portNumber.
     * @param number The number.
     */
void Connection::setPortNumber(const int number) {
     portNumber = number;
}

/**
    * @brief Implents the method of Connection like a server.
    */
ServerConnection::ServerConnection() : Connection(TypeConnection::SERVER) {}

/**
    * @brief Implents the method of Connection like a server.
    */
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

/**
    * @brief Implents the method of Connection like a server.
     * @return The message recieve.
    */
string ServerConnection::getMessage() {
    int n = 256;
    char buffer[n];
    bzero(buffer,n);
    numberCharactersIO = read(newSocketOutput, buffer, n-1);
    if (numberCharactersIO < 0) error("ERROR reading from socket");
    return string (buffer);
}

/**
    * @brief Implents the method of Connection like a server.
     * @param message The message to send.
    */
void ServerConnection::sendMessage(string message) {
    int n = message.length() + 1;
    char buffer[n];
    bzero(buffer,n);
    strcpy(buffer, message.c_str());
    numberCharactersIO = write(newSocketOutput, buffer, strlen(buffer));
    if (numberCharactersIO < 0) error("ERROR writing to socket");
    return;
}

/**
     * @brief Implents the method of Connection like a server.
     */
ServerConnection::~ServerConnection() {
    close( newSocketOutput);
}

/**
     * @brief Implents the method of Connection like a client.
     */
ClientConnection::ClientConnection() : Connection(TypeConnection::CLIENT) {
}

/**
    * @brief Implents the method of Connection like a client.
    */
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

/**
    * @brief Implents the method of Connection like a client.
     * @return The message recieve.
    */
string ClientConnection::getMessage() {
    int n = 256;
    char buffer[n];
    bzero(buffer,n);
    numberCharactersIO = read(socketOutput, buffer, 255);
    if (numberCharactersIO < 0)
        error("ERROR reading from socket");
    return string (buffer);
}

/**
    * @brief Implents the method of Connection like a client.
     * @param message The message to send.
    */
void ClientConnection::sendMessage(string message) {
    int n = message.length() + 1;
    char buffer[n];
    bzero(buffer,n);
    strcpy(buffer, message.c_str());
    numberCharactersIO = write(socketOutput, buffer, strlen(buffer));
    if (numberCharactersIO < 0)
        error("ERROR writing to socket");
    return;
}
