#include "messageprinting.h"




 // serverMessages::Alert createAlertMessage( serverMessages::Alert::AlertType alertType);


std::unordered_map< ServerAlertEnum, std::string> getAlertNames(){
    std::unordered_map< ServerAlertEnum, std::string> names;
    names[ServerAlertEnum::Alert_AlertType_DEFAULT] = "";
    names[ServerAlertEnum::Alert_AlertType_OK] = "OK";
    names[ServerAlertEnum::Alert_AlertType_SEND_FAILED] = "TEXT MESSAGE SENDING FAILED";
    names[ServerAlertEnum::Alert_AlertType_PING_RECEIVED] = "PING RECEIVED";
    names[ServerAlertEnum::Alert_AlertType_TEXT_RECEIVED] = "TEXT MESSAGE SENDING SUCEEDED";

 

    return names;

}
const std::unordered_map< ServerAlertEnum, std::string> ALERTS_DICTIONARY= getAlertNames();
 

 


void printAlert(const serverMessages::Alert &response){
            std::string alertName = ALERTS_DICTIONARY.at(response.type());
            std::cout << " Time (ms):    "  <<  response.time_ms()  << "\n";
            std::cout << " Alert:    "  <<     alertName  << "\n\n";

}

void printText(const chatMessages::TextMessage &text){
        std::cout << " Time: (ms)   "  <<  text.time_ms()  << "\n";
        std::cout << " Name:    "  <<  text.name()     << "\n";
        std::cout << " Text:    "  <<  text.text()     << "\n\n";

}
    
                
 