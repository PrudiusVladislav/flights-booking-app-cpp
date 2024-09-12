#include "TicketsService.h"
#include <stdexcept>

std::shared_ptr<Ticket> TicketsService::view(const int id) const {
    return _ticketsRepository->getById(id);
}

std::vector<std::shared_ptr<Ticket>> TicketsService::viewForUser(const std::string &username) const {
    return _ticketsRepository->getByUsername(username);
}

std::vector<std::shared_ptr<Ticket>> TicketsService::viewAvailable(const FlightIdentifier &identifier) const {
    return _ticketsRepository->getAll(identifier, false);
}

std::vector<std::shared_ptr<Ticket>> TicketsService::viewBooked(const FlightIdentifier &identifier) const {
    return _ticketsRepository->getAll(identifier, true);
}

int TicketsService::book(const BookingRequest &request) {
    FlightIdentifier identifier(request.date, request.flightNumber);
    std::vector<std::shared_ptr<Ticket>> availableTickets = _ticketsRepository->getAll(identifier, false);

    auto it = std::find_if(availableTickets.begin(), availableTickets.end(), [&](const std::shared_ptr<Ticket>& ticket) {
        return ticket->getSeat().getRow() == request.seat.getRow() &&
            ticket->getSeat().getSeatLetter() == request.seat.getSeatLetter();
    });

    if (it == availableTickets.end()) {
        throw std::runtime_error("Requested seat is not available");
    }

    std::shared_ptr<Ticket> ticket = *it;
    ticket->book(request.username);
    return ticket->getId();
}

void TicketsService::returnWithRefund(const int id) {
    auto ticket = _ticketsRepository->getById(id);
    if (!ticket) {
        throw std::runtime_error("Ticket not found");
    }
    if (!ticket->isBooked()) {
        throw std::runtime_error("Ticket is not booked");
    }
    ticket->cancel();
    _ticketsRepository->remove(id);
}