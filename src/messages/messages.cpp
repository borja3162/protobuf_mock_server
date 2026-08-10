#include "messages.h"

#include <chrono>



uint64_t now_ms()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}


serverMessages::Ping createPingMessage(){

 serverMessages::Ping ping;
 ping.set_time_ms( now_ms());

 return ping;

}


serverMessages::Alert createAlertMessage( const  serverMessages::Alert::AlertType  alertType){


    serverMessages::Alert alertMsg;
    alertMsg.set_time_ms(now_ms());
    alertMsg.set_type(alertType);

    return alertMsg;

}


chatMessages::TextMessage createTextMessage(  const std::string text, const std::string name ){

    chatMessages::TextMessage msg;

    msg.set_time_ms(now_ms());
    msg.set_name(name);
    msg.set_text(text);

    return msg;



}



