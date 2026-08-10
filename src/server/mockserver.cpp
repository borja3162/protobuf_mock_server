#include "mockserver.h"


#include "messages/messages.h"
#include "messages/messageprinting.h"


#include "server.pb.h"
#include "chat.pb.h"

#include "iostream"



 
    bool MockServer::processSerializedText( const SerializedText& serializedMsg) const{
        chatMessages::TextMessage msg;
        if( msg.ParseFromString(  serializedMsg.buffer ) ){

            printText(msg);       


            return true;
        }
        
        return false;

    }

    void MockServer::serializeAndAddAlertToResponse( const serverMessages::Alert &alert  , ServerResponse &response) const{

        SerializedAlert serAlert;
        if( alert.SerializeToString( &( serAlert.buffer) ) ){

            response.push_back(serAlert);
        }

    }



    ServerResponse MockServer::receivePing(const SerializedPing &serializedPing) const {
        
        std::cout <<  "  [SERVER] Ping received \n";
        serverMessages::Alert pingResponse= createAlertMessage( 
                            serverMessages::Alert_AlertType::Alert_AlertType_PING_RECEIVED );
        

        std::vector< SerializedAlert > response;
        serializeAndAddAlertToResponse(pingResponse , response);

        // SerializedAlert serAlert;
        // if( pingResponse.SerializeToString( &( serAlert.buffer) ) ){

        //     response.push_back(serAlert);
        // }
        
        std::cout  << "  [SERVER] Ping response size "<< response.size() << "\n";
        return response;


    }

    ServerResponse MockServer::receive( const SerializedText &serializedMsg) const {
        ServerResponse response;

        std::cout <<  "  [SERVER] Text received \n";

        bool success = processSerializedText(serializedMsg);
        if(!success){
            serverMessages::Alert alert= createAlertMessage( 
                            serverMessages::Alert_AlertType::Alert_AlertType_SEND_FAILED);
            serializeAndAddAlertToResponse(alert , response);
            
        }else{
            serverMessages::Alert alert= createAlertMessage( 
                    serverMessages::Alert_AlertType::Alert_AlertType_TEXT_RECEIVED);
            serializeAndAddAlertToResponse(alert , response);
            
        }


        return response;

    }


    bool MockServer::connect() const {
        std::cout  << "  [SERVER] Establishing a connection \n";
        return true;
    }




    