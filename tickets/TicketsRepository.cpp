//
// Created by Vladyslav Prudius  on 10.09.2024.
//

#include "TicketsRepository.h"
#include "../flights/FlightsRepository.h"
#include "Ticket.h"


void TicketsRepository::populateTickets() {
    const std::vector<Flight> flights = _flightsRepository->getAll();
    for (const Flight& flight : flights) {
        std::vector<Ticket> tickets = flight.getAllTickets();
        for (const Ticket& ticket : tickets) {
            add(ticket);
        }
    }
}

Ticket* TicketsRepository::getById(const int id) {
    for (Ticket& ticket : _tickets) {
        if (ticket.getId() == id) {
            return &ticket;
        }
    }
    return nullptr;
}

std::vector<Ticket> TicketsRepository::getByUsername(const std::string &username) {
    std::vector<Ticket> userTickets;
    for (const Ticket& ticket : _tickets) {
        if (ticket.getUsername() == username) {
            userTickets.push_back(ticket);
        }
    }
    return userTickets;
}

std::vector<Ticket> TicketsRepository::getAll(const FlightIdentifier &flightIdentifier, bool booked) {
    std::vector<Ticket> availableTickets;
    for (const Ticket& ticket : _tickets) {
        const bool isMatchingDate = ticket.getFlight().getDate() == flightIdentifier.getDate();
        const bool isMatchingFlightNumber = ticket.getFlight().getFlightNumber() == flightIdentifier.getFlightNumber();
        if (isMatchingDate && isMatchingFlightNumber && ticket.isBooked() == booked) {
            availableTickets.push_back(ticket);
        }
    }
    return availableTickets;
}

int TicketsRepository::add(Ticket ticket) {
    ticket.setId(++_lastId);
    _tickets.push_back(ticket);
    return ticket.getId();
}

void TicketsRepository::remove(int id) {
    std::erase_if(_tickets, [id](const Ticket& ticket) {
        return ticket.getId() == id;
    });
}
