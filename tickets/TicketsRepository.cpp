#include "TicketsRepository.h"
#include "../flights/FlightsRepository.h"
#include "Ticket.h"

void TicketsRepository::populateTickets() {
    const std::vector<Flight> flights = _flightsRepository->getAll();
    for (const Flight& flight : flights) {
        std::vector<std::shared_ptr<Ticket>> tickets = flight.getAllTickets();
        for (const auto& ticket : tickets) {
            add(ticket);
        }
    }
}

std::shared_ptr<Ticket> TicketsRepository::getById(const int id) {
    auto it = _ticketsById.find(id);
    if (it != _ticketsById.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<std::shared_ptr<Ticket>> TicketsRepository::getByUsername(const std::string &username) {
    auto it = _ticketsByUsername.find(username);
    if (it != _ticketsByUsername.end()) {
        return it->second;
    }
    return {};
}

std::vector<std::shared_ptr<Ticket>> TicketsRepository::getAll(const FlightIdentifier &flightIdentifier, const bool booked) {
    std::vector<std::shared_ptr<Ticket>> result;
    auto it = _ticketsByFlight.find(flightIdentifier);
    if (it != _ticketsByFlight.end()) {
        for (const auto& ticket : it->second) {
            if (ticket->isBooked() == booked) {
                result.push_back(ticket);
            }
        }
    }

    return result;
}

int TicketsRepository::add(const std::shared_ptr<Ticket> &ticket) {
    ticket->setId(++_lastId);
    _ticketsById[ticket->getId()] = ticket;
    _ticketsByUsername[ticket->getUsername()].push_back(ticket);
    const FlightIdentifier flight = ticket->getFlight();
    _ticketsByFlight[flight].push_back(ticket);

    return ticket->getId();
}