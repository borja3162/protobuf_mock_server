#include "connection.h"

#include "messages/messages.h"
#include "messages/messageprinting.h"


#include <stdexcept>




ServerConnection::ServerConnection( std::string clientIP, int clientPort)
                 :clientSocket(clientIP, clientPort),
                 server(nullptr), isConnectionActive(false){

     }
         




void ServerConnection::connectToServer(ServerInterface* server){

    std::cout << "  [CONNECTION] Connecting to server \n";

    if(server == nullptr){
        throw std::invalid_argument("Server to connect to must not be nullptr");
    }


    isConnectionActive = server->connect();
    if( isConnectionActive){
        this->server = server;
    }else{
        this->server = nullptr;
    }
}

void ServerConnection::updateReceivedAlertsQueue(ServerResponse &response ){

    for (int k = 0 ; k< response.size() ; k++){
        if(receivedAlerts.size() < MAX_QUEUE_SIZE){
            receivedAlerts.push( response[k]);
        }else{
            std::cout << " Alert queue is full \n";

        }
        
    }


}

void ServerConnection::sendSerializedMessage(const SerializedText &serMessage){

       //server->receive()
        std::cout << "  [CONNECTION] Sending serialized message to server \n";

        ServerResponse  response =  server->receive(serMessage);
        updateReceivedAlertsQueue(response);
        

    
}


void ServerConnection::sendTextMessage(const std::string &text, const std::string &username){

        std::cout << "  [CONNECTION] Sending message to server \n";
        chatMessages::TextMessage msg = createTextMessage(text, username);
        SerializedText serMessage;
        msg.SerializeToString(& (serMessage.buffer) );

        if(! isActive()){
            if(sendQueue.size() < MAX_QUEUE_SIZE ){
                sendQueue.push(serMessage);
            }else{
                std::cout << " Send queue is full \n";
                
            }
            
            return;
        }

        sendSerializedMessage(serMessage);


    }


    bool ServerConnection::isActive() const{
        return isConnectionActive && ! (server == nullptr );
    }










void ServerConnection::pingServer(){

    std::cout << "  [CONNECTION] pinging server \n";

    
    serverMessages::Ping  ping = createPingMessage();
    SerializedPing serPing ;
    ping.SerializeToString(& serPing.buffer);
    if (!isActive()){
        return;
        

    }

    ServerResponse  response = server->receivePing(serPing);
    updateReceivedAlertsQueue(response);
    
    


}



void ServerConnection::retrySending(){
    while ( (! sendQueue.empty() ) && isActive() ) {
            sendSerializedMessage( sendQueue.front());
             sendQueue.pop();
        }

}



void ServerConnection::displayReceivedAlerts( ){

    std::cout << "  [CONNECTION] Number of queued alerts: "<< receivedAlerts.size()  << "\n";
    while ( ! receivedAlerts.empty()  ) {

            std::unordered_map< ServerAlertEnum, std::string> alertNames = getAlertNames();
            
            serverMessages::Alert response;

            if (response.ParseFromString( receivedAlerts.front().buffer)  ) {

                printAlert(response);
                
            }
            

            receivedAlerts.pop();
        }


}


