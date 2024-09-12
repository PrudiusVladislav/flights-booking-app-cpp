//
// Created by Vladyslav Prudius  on 10.09.2024.
//

#include "FlightsRepository.h"

#include <fstream>
#include <iostream>

#include "Flight.h"
#include <sstream>
#include <vector>
#include <map>


// 01.03.2023 TI678 6 1-25 145$ 26-50 100$
// priceRangeStarts[0] = 1 ->> 145
// priceRangeStarts[1] = 26 ->> 100
// totalSeats = 50

Flight parseFlightString(const std::string& flightString) {
    std::istringstream iss(flightString);

    std::string date, flightNumber;
    int seatsPerRow;
    std::vector<SeatPriceRange> pricePerRangeStarts;
    int totalSeats = 0;

    iss >> date >> flightNumber >> seatsPerRow;
    if (iss.fail() || date.empty() || flightNumber.empty() || seatsPerRow <= 0) {
        throw std::runtime_error("Invalid flight string format");
    }

    std::string seatsRangeStr;
    std::string priceStr;
    while (iss >> seatsRangeStr >> priceStr) {
        size_t dashPos = seatsRangeStr.find('-');
        size_t dollarPos = priceStr.find('$');
        if (dashPos == std::string::npos || dollarPos == std::string::npos) {
            continue;
        }

        int startRow = std::stoi(seatsRangeStr.substr(0, dashPos));
        int endRow = std::stoi(seatsRangeStr.substr(dashPos + 1));
        int price = std::stoi(priceStr.substr(0, dollarPos));
        if (startRow <= 0 || endRow <= 0 || price <= 0 || startRow > endRow) {
            throw std::runtime_error("Invalid seat range or price");
        }
        pricePerRangeStarts.push_back({ startRow, endRow, price });
        totalSeats = std::max(totalSeats, endRow);
    }

    return { date, flightNumber, seatsPerRow, pricePerRangeStarts, totalSeats };
}

std::vector<Flight> FlightsRepository::getAll() const {
    std::vector<Flight> flights;
    std::ifstream file(_configPath);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << _configPath << std::endl;
        return flights;
    }

    std::string line;
    std::getline(file, line);
    const int numberOfRecords = std::stoi(line);

    for (int i = 0; i < numberOfRecords; ++i) {
        std::getline(file, line);

        flights.push_back(parseFlightString(line));
    }

    return flights;
}
