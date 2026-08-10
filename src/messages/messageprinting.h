#ifndef MESSAGEPRINTING_H
#define MESSAGEPRINTING_H

#include "server.pb.h"
#include "chat.pb.h"

#include "string"
#include "unordered_map"



using ServerAlertEnum = serverMessages::Alert::AlertType;
// serverMessages::Alert createAlertMessage( serverMessages::Alert::AlertType alertType);



std::unordered_map< ServerAlertEnum, std::string> getAlertNames();

extern const std::unordered_map< ServerAlertEnum, std::string> ALERTS_DICTIONARY;



void printAlert(const serverMessages::Alert &response);

void printText(const chatMessages::TextMessage &text);
                
  
 









#endif // MESSAGEPRINTING_H
