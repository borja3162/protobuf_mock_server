#ifndef NETWORKSTRUCTS_H
#define NETWORKSTRUCTS_H


#include "string"

struct NetworkSocket{
    std::string ip;
    int port;
    NetworkSocket(std::string ip, int port):
        ip(ip), port(port){

    }

};






#endif // NETWORKSTRUCTS_H
