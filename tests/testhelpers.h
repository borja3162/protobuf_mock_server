
#ifndef TESTHELPERS_H
#define TESTHELPERS_H



#include "messages/serializedtypes.h"
#include "messages/messages.h"




// #include "server.pb.h"
#include "chat.pb.h"




#include "string"




const std::string MESSAGE_TEXT = "message123";
const std::string MESSAGE_NAME = "Vincent";

SerializedText getSerializedMessageExample(){

    chatMessages::TextMessage msg = createTextMessage(MESSAGE_TEXT, MESSAGE_NAME);
        SerializedText serMessage;
        msg.SerializeToString(& (serMessage.buffer) );
    return serMessage;



}










#endif // TESTHELPERS_H


