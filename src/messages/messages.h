#ifndef PROTOMESSAGES_H
#define PROTOMESSAGES_H

#include "server.pb.h"
#include "chat.pb.h"
#include "string"




serverMessages::Ping createPingMessage();

serverMessages::Alert createAlertMessage( serverMessages::Alert::AlertType alertType);




chatMessages::TextMessage createTextMessage(  const std::string text, const std::string name );




#endif // PROTOMESSAGES_H
