#ifndef CLIENT_H
#define CLIENT_H


#include "memory"
#include "string"


#include "server/serverinterface.h"


struct UserPublicInfo{
    std::string name;

    UserPublicInfo(){
        name="Anonymous";
    }
};



class ServerConnection;

class Client{

private:
    bool isConnected;
    std::string ip;
    int port;
    std::unique_ptr < ServerConnection > conn;


    UserPublicInfo userInfo;

public:
    Client(std::string clientIP = "111.111.111.111",
                     int clientPort = 8085);

    void connectToServer( ServerInterface* server);

    void setUser( std::string name);

    void pingServer();
    void sendTextMessage( const std::string text);
    std::vector < std::string > readServerNotifications(); 
    
    void readNotifications();

    //std::vector< Alert > returned by connection

  

};

 

#endif // CLIENT_H
