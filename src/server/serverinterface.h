#ifndef SERVERINTERFACE_H
#define SERVERINTERFACE_H


#include "messages/serializedtypes.h"
#include "server.pb.h"
#include "vector"



using ServerResponse = std::vector< SerializedAlert >;


class ServerInterface{

public:
    virtual bool connect() const = 0;
     
    // virtual std::vector< SerializedAlert > receive( SerializedText serializedMsg) const= 0;


    virtual ServerResponse receivePing(const SerializedPing &serializedPing) const {
        ServerResponse emptyResponse;
        return emptyResponse;
    }


    virtual ServerResponse receive( const SerializedText &serializedMsg) const= 0;





};


 




#endif // SERVERINTERFACE_H
