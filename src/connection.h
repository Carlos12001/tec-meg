//
// Created by carlo on 3/27/22.
//

#ifndef TEC_MEG_CONNECTION_H
#define TEC_MEG_CONNECTION_H

enum TypeConnection{
    SERVER, CLIENT
};

class Connection {
public:
    const TypeConnection type;
    int socketOutput;
    int portNumber;
    int numberCharactersIO;
    char* buffer = nullptr;

    Connection(TypeConnection type);

    void error(const char* message);

    virtual void initSocket();

    virtual ~Connection();
};


#endif //TEC_MEG_CONNECTION_H
