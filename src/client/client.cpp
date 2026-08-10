
#include "client/client.h"
#include "string"
#include "networking/connection.h"




 Client::Client(std::string clientIP ,
                     int clientPort )
                     : ip(clientIP) , port(clientPort) {


 }




void Client::connectToServer(ServerInterface* server){

     conn = std::make_unique< ServerConnection >(ip, port); // deletes previous one if it already existed
     conn->connectToServer(server);


}


void Client::setUser( std::string name){
    userInfo.name = name;
}

void Client::pingServer(){

    conn->pingServer();
}

void Client::sendTextMessage( const std::string text){

    conn->sendTextMessage(text, userInfo.name);
}

void Client::readNotifications(){
    conn->displayReceivedAlerts();
}


