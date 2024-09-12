//
// Created by Vladyslav Prudius  on 10.09.2024.
//

#include "Ticket.h"

void Ticket::book(const std::string &username){
    _isBooked = true;
    _username = username;
}

void Ticket::cancel(){
    _isBooked = false;
    _username = "";
}

