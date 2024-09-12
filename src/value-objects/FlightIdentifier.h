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

    bool operator==(const FlightIdentifier & flight_identifier) const {
        return _date == flight_identifier._date && _flightNumber == flight_identifier._flightNumber;
    }
};

namespace std {
    template <>
    struct hash<FlightIdentifier> {
        std::size_t operator()(const FlightIdentifier &key) const noexcept {
            return hash<std::string>()(key.getDate()) ^
                   hash<std::string>()(key.getFlightNumber());
        }
    };
}

#endif //FLIGHTIDENTIFIER_H
