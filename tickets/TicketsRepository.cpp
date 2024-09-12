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
    for (const auto& ticket : _tickets) {
        if (ticket->getId() == id) {
            return ticket;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Ticket>> TicketsRepository::getByUsername(const std::string &username) {
    std::vector<std::shared_ptr<Ticket>> userTickets;
    for (const auto& ticket : _tickets) {
        if (ticket->getUsername() == username) {
            userTickets.push_back(ticket);
        }
    }
    return userTickets;
}

std::vector<std::shared_ptr<Ticket>> TicketsRepository::getAll(const FlightIdentifier &flightIdentifier, bool booked) {
    std::vector<std::shared_ptr<Ticket>> availableTickets;
    for (const auto& ticket : _tickets) {
        const bool isMatchingDate = ticket->getFlight().getDate() == flightIdentifier.getDate();
        const bool isMatchingFlightNumber = ticket->getFlight().getFlightNumber() == flightIdentifier.getFlightNumber();
        if (isMatchingDate && isMatchingFlightNumber && ticket->isBooked() == booked) {
            availableTickets.push_back(ticket);
        }
    }
    return availableTickets;
}

int TicketsRepository::add(std::shared_ptr<Ticket> ticket) {
    ticket->setId(++_lastId);
    _tickets.push_back(ticket);
    return ticket->getId();
}

void TicketsRepository::remove(int id) {
    _tickets.erase(std::ranges::remove_if(_tickets, [id](const std::shared_ptr<Ticket>& ticket) {
        return ticket->getId() == id;
    }).begin(), _tickets.end());
}