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

/**
 * @brief Say the type of the connection.
 */
enum TypeConnection{
    SERVER, CLIENT
};

/**
 * @brief Is abstract class of the connections. The connection father, is only to apply good practices.
 */
class Connection {
protected:

    /**
     * @brief Stores the type of the connection.
     */
    const TypeConnection type;

    /**
     * @brief Check is it was previously inited.
     */
    bool inited = false;

    /**
     * @brief The output of the socket.
     */
    int socketOutput{};

    /**
     * @brief The number of the port.
     */
    int portNumber = 8080;

    /**
     * @brief The number of characters of the message.
     */
    int numberCharactersIO{};

    /**
     * @brief The address of the server socket.
     */
    struct sockaddr_in serverAddress{};

    /**
     * @brief Print it was a an error.
     * @param message The message to print.
     */
    static void error(const string& message);
public:

    /**
     *
     * @brief The constructor of the class.
     * @param type Decide the type of the connection.
     */
    Connection(TypeConnection type);

    /**
     * @brief Init the type of the connection.
     */
    virtual void initConnection() = 0;

    /**
     * @brief Get an message of the connection.
     * @return The message recieve.
     */
    virtual string getMessage() = 0;

    /**
     * @brief Send an message of the connection.
     * @param message The message to send.
     */
    virtual void sendMessage(string message) = 0;

    /**
     * @brief Close all the connections.
     */
    virtual ~Connection();

    /**
     * @brief Set of the param portNumber.
     * @param number The number.
     */
    void setPortNumber(const int number);
};

/**
 * @brief Implents the methods of Connection like a server.
 */
class ServerConnection: public Connection{
protected:

    /**
     * @brief The final socket to use to comunicate.
     */
    int newSocketOutput = -1;

    /**
     * @brief The size of the address of the client.
     */
    socklen_t clientAddressSize;

    /**
     * @brief The address of the client.
     */
    struct sockaddr_in clientAddress;
public:

    /**
    * @brief Implents the method of Connection like a server.
    */
    ServerConnection();

    /**
    * @brief Implents the method of Connection like a server.
    */
    void initConnection() override;

    /**
    * @brief Implents the method of Connection like a server.
     * @return The message recieve.
    */
    string getMessage() override;

    /**
    * @brief Implents the method of Connection like a server.
     * @param message The message to send.
    */
    void sendMessage(string message) override;

    /**
     * @brief Implents the method of Connection like a server.
     */
    ~ServerConnection();
};

/**
* @brief Implents the method of Connection like a client.
*/
class ClientConnection: public Connection{
protected:

    /**
     * @brief The host information.
     */
    struct hostent* serverHost = nullptr;

    /**
     * The IP of the connection.
     */
    const char* ipHost = "localhost";

public:

    /**
     * @brief Implents the method of Connection like a client.
     */
    ClientConnection();

    /**
     * @brief Set what id IP address.
     * @param IP address.
     */
    void setIpHost(string host);

    /**
    * @brief Implents the method of Connection like a client.
    */
    void initConnection() override;

    /**
    * @brief Implents the method of Connection like a client.
     * @return The message recieve.
    */
    string getMessage() override;

    /**
    * @brief Implents the method of Connection like a client.
     * @param message The message to send.
    */
    void sendMessage(string message) override;
};

#endif //TEC_MEG_CONNECTION_H
