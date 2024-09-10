//
// Created by Vladyslav Prudius  on 10.09.2024.
//

#include "TicketsService.h"

#include <algorithm>
#include <stdexcept>

Ticket* TicketsService::view(const int id) const {
    return _ticketsRepository->getById(id);
}

std::vector<Ticket> TicketsService::viewForUser(const std::string &username) const {
    return _ticketsRepository->getByUsername(username);
}

std::vector<Ticket> TicketsService::viewAvailable(const FlightIdentifier &identifier) const {
    return _ticketsRepository->getAll(identifier, false);
}

std::vector<Ticket> TicketsService::viewBooked(const FlightIdentifier &identifier) const {
    return _ticketsRepository->getAll(identifier, true);
}

int TicketsService::book(const BookingRequest &request) {
    FlightIdentifier identifier(request.date, request.flightNumber);
    std::vector<Ticket> availableTickets = _ticketsRepository->getAll(identifier, false);

    auto it = std::find_if(availableTickets.begin(), availableTickets.end(), [&](const Ticket &ticket) {
        return ticket.getSeat().getRow() == request.seat.getRow() &&
            ticket.getSeat().getSeatLetter() == request.seat.getSeatLetter();
    });

    if (it == availableTickets.end()) {
        throw std::runtime_error("Requested seat is not available");
    }

    Ticket* ticket = _ticketsRepository->getById(it->getId());
    if (!ticket) {
        throw std::runtime_error("Ticket not found");
    }

    ticket->book(request.username);
    return ticket->getId();
}

void TicketsService::returnWithRefund(const int id) {
    Ticket* ticket = _ticketsRepository->getById(id);
    if (!ticket) {
        throw std::runtime_error("Ticket not found");
    }

    if (!ticket->isBooked()) {
        throw std::runtime_error("Ticket is not booked");
    }

    ticket->cancel();
}