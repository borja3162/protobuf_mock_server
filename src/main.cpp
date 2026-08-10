#include <google/protobuf/message.h>
#include <iostream>



#include "messages/messages.h"
#include "messages/serializedtypes.h"
#include "messages/messageprinting.h"


#include "server/mockserver.h"
#include "client/client.h"
#include "networking/connection.h"

void mainEncodeDecode(){

     chatMessages::TextMessage msg = createTextMessage("abcde\n     f","John");
     std::string serialized_buffer ;
     if ( ! (  msg.SerializeToString( &serialized_buffer )   )   ){
        std::cout << " error serializing message \n";
        return;

     }


    chatMessages::TextMessage msg2;

    if (msg2.ParseFromString(serialized_buffer))
    {
        printText(msg2);       
    }else{
        std::cout << " error deserializing message \n";

    }



}



void mainClient(){


    Client client;
    MockServer server;
    client.connectToServer( &server );

    

    client.sendTextMessage("anonymous text");
    client.setUser("Sam");
    client.pingServer();
    client.sendTextMessage("text1");
    client.sendTextMessage("text2");

    client.readNotifications();


}




int main()
{
    std::cout << " ---- start ------- \n";


    GOOGLE_PROTOBUF_VERIFY_VERSION;



    mainEncodeDecode();

    mainClient();


  

    std::cin.get();

    return 0;
}
