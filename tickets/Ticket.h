//
// Created by Vladyslav Prudius  on 10.09.2024.
//

#ifndef TICKET_H
#define TICKET_H
#include <string>

#include "../value-objects/Seat.h"
#include "../value-objects/FlightIdentifier.h"

class Ticket {
    int _id;
    FlightIdentifier _flight;
    bool _isBooked;
    std::string _username;
    Seat _seat;
    int _price;
public:
    Ticket(
        FlightIdentifier flight,
        const bool isBooked,
        std::string username,
        const Seat seat,
        const int price) :
        _flight(std::move(flight)),
        _isBooked(isBooked),
        _username(std::move(username)),
        _seat(seat),
        _price(price) {}

    Ticket(const Ticket& other) :
        _flight(other._flight),
        _isBooked(other._isBooked),
        _username(other._username),
        _seat(other._seat),
        _price(other._price) {}

    Ticket& operator=(const Ticket& other) {
        if (this == &other) {
            return *this;
        }
        _flight = other._flight;
        _isBooked = other._isBooked;
        _username = other._username;
        _seat = other._seat;
        _price = other._price;
        return *this;
    }

    void book(const std::string &username);
    void cancel();

    [[nodiscard]] int getId() const {
        return _id;
    }

    void setId(const int id) {
        _id = id;
    }

    [[nodiscard]] std::string getUsername() const {
        return _username;
    }

    [[nodiscard]] FlightIdentifier getFlight() const {
        return _flight;
    }

    [[nodiscard]] bool isBooked() const {
        return _isBooked;
    }

    [[nodiscard]] Seat getSeat() const {
        return _seat;
    }

    [[nodiscard]] int getPrice() const {
        return _price;
    }
};


#endif //TICKET_H
