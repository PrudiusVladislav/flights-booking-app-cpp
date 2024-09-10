//
// Created by Vladyslav Prudius  on 10.09.2024.
//

#ifndef FLIGHTIDENTIFIER_H
#define FLIGHTIDENTIFIER_H


class FlightIdentifier {
    std::string _date;
    std::string _flightNumber;

public:
    FlightIdentifier(std::string date, std::string flightNumber)
        : _date(std::move(date)), _flightNumber(std::move(flightNumber)) {}

    [[nodiscard]] std::string getDate() const {
        return _date;
    }

    [[nodiscard]] std::string getFlightNumber() const {
        return _flightNumber;
    }
};

#endif //FLIGHTIDENTIFIER_H
