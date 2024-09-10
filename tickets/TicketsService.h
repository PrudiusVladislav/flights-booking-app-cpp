//
// Created by Vladyslav Prudius  on 10.09.2024.
//

#ifndef TICKETSSERVICE_H
#define TICKETSSERVICE_H
#include <string>

#include "Ticket.h"
#include "TicketsRepository.h"

struct BookingRequest {
    std::string username;
    std::string date;
    std::string flightNumber;
    Seat seat;
};

class TicketsService {
    TicketsRepository* _ticketsRepository;
public:
    explicit TicketsService(TicketsRepository* ticketsRepository): _ticketsRepository(ticketsRepository) {}

    Ticket* view(int id) const;
    std::vector<Ticket> viewForUser(const std::string &username) const;
    std::vector<Ticket> viewAvailable(const FlightIdentifier &identifier) const;
    std::vector<Ticket> viewBooked(const FlightIdentifier &identifier) const;

    int book(const BookingRequest &request);
    void returnWithRefund(int id);
};



#endif //TICKETSSERVICE_H
