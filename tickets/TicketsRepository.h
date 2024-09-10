//
// Created by Vladyslav Prudius  on 10.09.2024.
//

#ifndef TICKETSREPOSITORY_H
#define TICKETSREPOSITORY_H
#include <vector>

#include "../flights/FlightsRepository.h"
#include "Ticket.h"


class TicketsRepository {
private:
    const FlightsRepository* _flightsRepository;
    std::vector<Ticket> _tickets = {};
    int _lastId = 0;

    void populateTickets();
public:
    explicit TicketsRepository(const FlightsRepository* flightsRepository): _flightsRepository(flightsRepository) {
        populateTickets();
    }

    Ticket* getById(int id);
    std::vector<Ticket> getByUsername(const std::string &username);
    std::vector<Ticket> getAll(const FlightIdentifier &flightIdentifier, bool booked);

    int add(Ticket ticket);
    void remove(int id);
};



#endif //TICKETSREPOSITORY_H
