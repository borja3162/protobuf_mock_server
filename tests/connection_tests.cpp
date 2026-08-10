#include <doctest/doctest.h>


// #include "messages/messages.h"
// #include "messages/messageprinting.h"
#include "messages/serializedtypes.h"
#include "networking/connection.h"
#include "server/serverinterface.h"
#include "server/mockserver.h"


#include "server.pb.h"
#include "chat.pb.h"

#include "string"
#include <queue>



// friend class to ServerConnection for testing
struct ConnectionTestAccess{


    static std::queue< SerializedText > const& getSendQueueRef( const ServerConnection& conn) {
        return conn.sendQueue;
    }
    static std::queue< SerializedAlert > const& getAlertsRef( const ServerConnection& conn) {
        return conn.receivedAlerts;
    }
 
    static int getMaxQueueSize(){
        return ServerConnection::MAX_QUEUE_SIZE;
    }
    

};





 


TEST_CASE("Connection with mock server") {
    
    
    MockServer server;
    const std::string clientIP = "111.111.111.111";
    const int clientPort = 8085;
    ServerConnection conn(clientIP, clientPort);


    //connect to mock server
    conn.connectToServer(&server);
    CHECK( conn.isActive());

    // send message and check alerts received 
    CHECK(    ConnectionTestAccess::getAlertsRef(conn).empty());
    conn.sendTextMessage("ABC", "D" );
    CHECK_FALSE(    ConnectionTestAccess::getAlertsRef(conn).empty());

    // read alerts and check queue is empty
    conn.displayReceivedAlerts();
    CHECK(    ConnectionTestAccess::getAlertsRef(conn).empty());

}
        

TEST_CASE("Connection without server ") {
    
    const std::string clientIP = "111.111.111.111";
    const int clientPort = 8085;
    ServerConnection conn(clientIP, clientPort);


    //check connection state
    CHECK_FALSE( conn.isActive());

    // try to send the message and check the text sending queue is now nonempty
    conn.sendTextMessage("ABC", "D" );
    CHECK(    ConnectionTestAccess::getAlertsRef(conn).empty());
    CHECK_FALSE(    ConnectionTestAccess::getSendQueueRef(conn).empty());

    
    // try to send the messages and check the max number of messages in queue isn't surpassed
    const int maxMessages = ConnectionTestAccess::getMaxQueueSize();
    for(int k = 0 ; k < maxMessages+2; k++){
        conn.sendTextMessage("ABC", "D" );
    }

    CHECK( ConnectionTestAccess::getSendQueueRef(conn).size() <= maxMessages) ;

}



