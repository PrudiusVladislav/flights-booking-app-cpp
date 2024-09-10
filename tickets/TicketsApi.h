//
// Created by Vladyslav Prudius  on 10.09.2024.
//

#ifndef TICKETSAPI_H
#define TICKETSAPI_H
#include "TicketsService.h"


class TicketsApi {
    TicketsService* _ticketsService;
    void processCommand(const std::string& command);
public:
    explicit TicketsApi(TicketsService* ticketsService): _ticketsService(ticketsService) {}

    void checkAvailability(const std::string& date, const std::string& flightNumber);
    void bookTicket(const std::string& date, const std::string& flightNumber, const std::string &seat, const std::string& username);
    void returnTicket(int ticketId);
    void viewById(int ticketId);
    void viewByUsername(const std::string& username);
    void viewFlight(const std::string& date, const std::string& flightNumber);
};



#endif //TICKETSAPI_H
