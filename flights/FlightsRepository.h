//
// Created by Vladyslav Prudius  on 10.09.2024.
//

#ifndef FLIGHTSREPOSITORY_H
#define FLIGHTSREPOSITORY_H
#include <string>
#include <utility>

#include "Flight.h"


class FlightsRepository {
private:
    const std::string _configPath;
public:
    explicit FlightsRepository(std::string configPath) : _configPath(std::move(configPath)) {}
    [[nodiscard]] std::vector<Flight> getAll() const;
};



#endif //FLIGHTSREPOSITORY_H
