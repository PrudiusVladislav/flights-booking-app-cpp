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
    std::unordered_map<int, std::shared_ptr<Ticket>> _ticketsById;
    std::unordered_map<std::string, std::vector<std::shared_ptr<Ticket>>> _ticketsByUsername;
    std::unordered_map<FlightIdentifier, std::vector<std::shared_ptr<Ticket>>> _ticketsByFlight;
    int _lastId = 0;

    void populateTickets();

public:
    explicit TicketsRepository(const FlightsRepository* flightsRepository): _flightsRepository(flightsRepository) {
        populateTickets();
    }

    std::shared_ptr<Ticket> getById(const int id);
    std::vector<std::shared_ptr<Ticket>> getByUsername(const std::string &username);
    std::vector<std::shared_ptr<Ticket>> getAll(const FlightIdentifier &flightIdentifier, bool booked);

    int add(const std::shared_ptr<Ticket> &ticket);
};



#endif //TICKETSREPOSITORY_H
