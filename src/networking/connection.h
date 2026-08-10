#ifndef CONNECTION_H
#define CONNECTION_H

#include "networkstructs.h"

#include "messages/serializedtypes.h"
#include "server/serverinterface.h"




#include "string"
#include "queue"






class ServerConnection{
    friend struct ConnectionTestAccess; // forward declaration so testing can have access to  the class private members
private:

    static const int MAX_QUEUE_SIZE = 25;


    const NetworkSocket clientSocket;

    bool isConnectionActive;

    // queue of messages going to the server, in case server is unavailable
    std::queue< SerializedText > sendQueue;
    // queue of incoming notificcations or alerts
    std::queue< SerializedAlert > receivedAlerts;


    // Lifetime of server is independent from connection
    ServerInterface* server;


    //! sends serialized message, and adds server serialized responses to receivedAlerts
    void sendSerializedMessage(const SerializedText &text);

    void updateReceivedAlertsQueue(ServerResponse &response );

public:
    ServerConnection( std::string clientIP,
                     int clientPort);

    
    void connectToServer(ServerInterface* server);


    void pingServer();


    void sendTextMessage(const std::string &text, const std::string &username);

    //! checks if connection with server was properly established 
    bool isActive() const;

    //! tries to send messages stored in the queue to the server
    void retrySending();


    //! shows all received alerts and deletes them from the alert queue
    void displayReceivedAlerts( );
    
};





#endif // CONNECTION_H
