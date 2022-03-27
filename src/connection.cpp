//
// Created by carlo on 3/27/22.
//

#include "connection.h"


Connection::Connection(TypeConnection type) : type(type) {}

Connection::~Connection() {
    delete this->buffer;
}
