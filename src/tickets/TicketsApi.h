//
// Created by Vladyslav Prudius  on 10.09.2024.
//

#ifndef TICKETSAPI_H
#define TICKETSAPI_H
#include "TicketsService.h"


class TicketsApi {
    TicketsService* _ticketsService;
    bool _running = true;

    void processCommand(const std::string& command);
    using CommandHandler = std::function<void(std::istringstream&)>;
    std::unordered_map<std::string, CommandHandler> _commandHandlers;

    void handleCheck(std::istringstream& iss);
    void handleBook(std::istringstream& iss);
    void handleReturn(std::istringstream& iss);
    void handleView(std::istringstream& iss);

    bool validateDateAndFlightNumber(const std::string& date, const std::string& flightNumber);
    bool validateBookingDetails(const std::string& date, const std::string& flightNumber, const std::string& seat, const std::string& username);
    bool validateTicketId(int id);

    void printTicket(const Ticket& ticket, const bool showUsername);
public:
    explicit TicketsApi(TicketsService* ticketsService);
    void run();

    void checkAvailability(const std::string& date, const std::string& flightNumber);
    void bookTicket(const std::string& date, const std::string& flightNumber, const std::string &seat, const std::string& username);
    void returnTicket(int ticketId);
    void viewById(int ticketId);
    void viewByUsername(const std::string& username);
    void viewFlight(const std::string& date, const std::string& flightNumber);
};



#endif //TICKETSAPI_H
