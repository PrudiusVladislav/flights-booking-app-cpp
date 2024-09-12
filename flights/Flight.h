//
// Created by Vladyslav Prudius  on 10.09.2024.
//

#ifndef FLIGHT_H
#define FLIGHT_H
#include <map>
#include <string>
#include "../tickets/Ticket.h"

class Flight {
public:
    std::string date;
    std::string flightNumber;
    int seatsPerRow;
    std::map<int, int> priceRangeStarts;
    int totalSeats;

    Flight(
        std::string date,
        std::string flightNumber,
        const int seatsPerRow,
        std::map<int, int> pricePerRowRange,
        const int totalSeats) :
        date(std::move(date)),
        flightNumber(std::move(flightNumber)),
        seatsPerRow(seatsPerRow),
        priceRangeStarts(std::move(pricePerRowRange)),
        totalSeats(totalSeats) {}

    [[nodiscard]] std::vector<Ticket> getAllTickets() const;
};


#endif //FLIGHT_H
