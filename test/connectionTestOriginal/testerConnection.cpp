#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;
class Utilities
{
public:
    static int inputStringToInt();
};

int Utilities::inputStringToInt() {
    int inputNumber, errorCounter = 0;
    string inputString;
    while (true){
        try {
            cin >> inputString;
            inputNumber = stoi(inputString);
            break;
        }
        catch (...){
            cerr << "Your input is not a number. It was: " << inputString << endl;
            errorCounter++;
            if (errorCounter>=20) { cerr<<"Many tries!" << endl;exit(-1);}
        }
    }
    return inputNumber;
}

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int server(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,
                       (struct sockaddr *) &cli_addr,
                       &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");
    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if (n < 0) error("ERROR reading from socket");
    printf("Here is the message: %s\n",buffer);
    n = write(newsockfd,"I got your message",18);
    if (n < 0) error("ERROR writing to socket");
    close(newsockfd);
    close(sockfd);
    return 0;
}

int client(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,
                       (struct sockaddr *) &cli_addr,
                       &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");
    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if (n < 0) error("ERROR reading from socket");
    printf("Here is the message: %s\n",buffer);
    n = write(newsockfd,"I got your message",18);
    if (n < 0) error("ERROR writing to socket");
    close(newsockfd);
    close(sockfd);
    return 0;
}
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

        connection->sendMessage("I got your message");

        delete connection;
        return;
    }

    static void testClientConnection(){
        auto connection = new ClientConnection;

        cout << "Please enter a number for the port: " << endl;
        int number =  Utilities::inputStringToInt();
        connection->setPortNumber(number);


        connection->initConnection();

        connection->sendMessage("");

        cout << connection->getMessage() << endl;

        delete connection;
        return;
    }
};