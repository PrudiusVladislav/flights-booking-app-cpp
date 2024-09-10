//
// Created by Vladyslav Prudius  on 10.09.2024.
//

#ifndef SEAT_H
#define SEAT_H
#include <string>

class  Seat {
    int _row;
    char _seat;

public:
    explicit Seat(const std::string& seat)
    : _row(std::stoi(seat.substr(0, seat.size() - 1))),
    _seat(seat[seat.size() - 1]) {}

    Seat(const int row, const char seat) : _row(row), _seat(seat) {}

    Seat(const Seat& other) : _row(other._row), _seat(other._seat) {}

    Seat& operator=(const Seat& other) {
        if (this == &other) {
            return *this;
        }
        _row = other._row;
        _seat = other._seat;
        return *this;
    }

    [[nodiscard]] int getRow() const {
        return _row;
    }

    [[nodiscard]] char getSeatLetter() const {
        return _seat;
    }

    [[nodiscard]] std::string toString() const {
        return std::to_string(_row) + _seat;
    }
};

#endif //SEAT_H
