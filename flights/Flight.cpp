//
// Created by Vladyslav Prudius  on 10.09.2024.
//

#include "Flight.h"
#include "../value-objects/Seat.h"
#include "../tickets/Ticket.h"

std::vector<std::shared_ptr<Ticket>> Flight::getAllTickets() const {
    std::vector<std::shared_ptr<Ticket>> tickets;
    const std::string seatLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    FlightIdentifier flightIdentifier = {date, flightNumber};

    for (const SeatPriceRange& seatPriceRange : seatsPriceRanges) {
        for (int row = seatPriceRange.startRow; row <= seatPriceRange.endRow; row++) {
            for (int seatIndex = 0; seatIndex < seatsPerRow; seatIndex++) {
                Seat seat = {row, seatLetters[seatIndex]};
                auto ticket = std::make_shared<Ticket>(flightIdentifier, false, "", seat, seatPriceRange.price);
                tickets.push_back(ticket);
            }
        }
    }

    return tickets;
}
