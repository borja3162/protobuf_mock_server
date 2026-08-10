#ifndef MOCKSERVER_H
#define MOCKSERVER_H

#include "serverinterface.h"

#include "messages/serializedtypes.h"


#include "vector"








class MockServer : public ServerInterface{

private:
    bool processSerializedText( const SerializedText& serializedMsg) const ;

    void serializeAndAddAlertToResponse( const serverMessages::Alert &alert  , std::vector< SerializedAlert > &response) const;


public:

    ServerResponse receivePing(const SerializedPing &serializedPing) const override;

    ServerResponse receive( const SerializedText &serializedMsg) const override;


    bool connect() const override;





};





#endif // MOCKSERVER_H
