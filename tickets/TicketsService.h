#ifndef TICKETSSERVICE_H
#define TICKETSSERVICE_H
#include <string>
#include <memory>
#include <vector>

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

    std::shared_ptr<Ticket> view(int id) const;
    std::vector<std::shared_ptr<Ticket>> viewForUser(const std::string &username) const;
    std::vector<std::shared_ptr<Ticket>> viewAvailable(const FlightIdentifier &identifier) const;
    std::vector<std::shared_ptr<Ticket>> viewBooked(const FlightIdentifier &identifier) const;

    int book(const BookingRequest &request);
    void returnWithRefund(int id);
};

#endif //TICKETSSERVICE_H