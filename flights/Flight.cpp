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

    for (const auto& [startRow, price] : pricePerRowRange) {
        for (int row = startRow; row <= startRow + seatsPerRow - 1; ++row) {
            for (int seatIndex = 0; seatIndex < seatsPerRow; ++seatIndex) {
                Seat seat = {row, seatLetters[seatIndex]};
                Ticket ticket(flightIdentifier, false, "", seat, price);
                tickets.push_back(ticket);
            }
        }
    }

    return tickets;
}
