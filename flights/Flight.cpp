//
// Created by Vladyslav Prudius  on 10.09.2024.
//

#include "Flight.h"
#include "../value-objects/Seat.h"
#include "../tickets/Ticket.h"

std::vector<Ticket> Flight::getAllTickets() const {
    std::vector<Ticket> tickets;
    const std::string seatLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    FlightIdentifier flightIdentifier = {date, flightNumber};

    for (const SeatPriceRange& seatPriceRange : seatsPriceRanges) {
        for (int row = seatPriceRange.startRow; row <= seatPriceRange.endRow; row++) {
            for (int seatIndex = 0; seatIndex < seatsPerRow; seatIndex++) {
                Seat seat = {row, seatLetters[seatIndex]};
                Ticket ticket(flightIdentifier, false, "", seat, seatPriceRange.price);
                tickets.push_back(ticket);
            }
        }
    }

    return tickets;
}
