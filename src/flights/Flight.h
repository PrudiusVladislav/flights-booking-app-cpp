//
// Created by Vladyslav Prudius  on 10.09.2024.
//

#ifndef FLIGHT_H
#define FLIGHT_H
#include <map>
#include <string>
#include "../tickets/Ticket.h"


struct SeatPriceRange {
    int startRow;
    int endRow;
    int price;
};

class Flight {
public:
    std::string date;
    std::string flightNumber;
    int seatsPerRow;
    std::vector<SeatPriceRange> seatsPriceRanges;
    int totalSeats;

    Flight(
        std::string date,
        std::string flightNumber,
        const int seatsPerRow,
        std::vector<SeatPriceRange> pricePerRowRange,
        const int totalSeats) :
        date(std::move(date)),
        flightNumber(std::move(flightNumber)),
        seatsPerRow(seatsPerRow),
        seatsPriceRanges(std::move(pricePerRowRange)),
        totalSeats(totalSeats) {}

    [[nodiscard]] std::vector<std::shared_ptr<Ticket>> getAllTickets() const;
};


#endif //FLIGHT_H
