#include <doctest/doctest.h>

#include "testhelpers.h"


#include "messages/messages.h"
#include "messages/serializedtypes.h"
#include "messages/messageprinting.h"

#include "server/serverinterface.h"
#include "server/mockserver.h"
//#include "networking/connection.h"


#include "server.pb.h"
#include "chat.pb.h"



#include "string"



 


bool checkAlertIsInResponse(const ServerResponse &response , serverMessages::Alert::AlertType alertType ){
    for (const SerializedAlert& serAlert : response ){
        serverMessages::Alert alert;
        if( alert.ParseFromString( serAlert.buffer) ){
            if(  alert.type() == alertType){
                return true;
            }
        }


    }

    return false;

}


TEST_CASE("Mock server receiving messages") {

        MockServer server;

        SerializedText serMessage =getSerializedMessageExample();
        ServerResponse response = server.receive(serMessage);

        const bool goodMessageAlert = checkAlertIsInResponse( response , ServerAlertEnum::Alert_AlertType_TEXT_RECEIVED);
        CHECK(goodMessageAlert);        



        SerializedText serInvalid;
        
        // the start of an encoded field-value pair, without a value. argument 1: number of bytes
        serInvalid.buffer =std::string ("\x08", 1);
        ServerResponse responseInvalid = server.receive(serInvalid);

        const bool badMessageAlert = checkAlertIsInResponse( responseInvalid , ServerAlertEnum::Alert_AlertType_SEND_FAILED);
        CHECK(badMessageAlert);        

}
        