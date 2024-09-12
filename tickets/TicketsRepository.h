//
// Created by Vladyslav Prudius  on 10.09.2024.
//

#ifndef TICKETSREPOSITORY_H
#define TICKETSREPOSITORY_H
#include <vector>

#include "../flights/FlightsRepository.h"
#include "Ticket.h"


class TicketsRepository {
    const FlightsRepository* _flightsRepository;
    std::vector<std::shared_ptr<Ticket>> _tickets = {};
    int _lastId = 0;

    void populateTickets();
public:
    explicit TicketsRepository(const FlightsRepository* flightsRepository): _flightsRepository(flightsRepository) {
        populateTickets();
    }

    std::shared_ptr<Ticket> getById(const int id);
    std::vector<std::shared_ptr<Ticket>> getByUsername(const std::string &username);
    std::vector<std::shared_ptr<Ticket>> getAll(const FlightIdentifier &flightIdentifier, bool booked);

    int add(std::shared_ptr<Ticket> ticket);
    void remove(int id);
};



#endif //TICKETSREPOSITORY_H
