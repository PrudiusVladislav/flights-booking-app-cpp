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

std::vector<Flight> FlightsRepository::getAll() const {
    std::vector<Flight> flights;
    std::ifstream file(_configPath);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << _configPath << std::endl;
        return flights;
    }

    int numberOfRecords;
    file >> numberOfRecords;

    for (int i = 0; i < numberOfRecords; ++i) {
        std::string date, flightNumber;
        int seatsPerRow;
        std::map<int, int> pricePerRowRange;

        file >> date >> flightNumber >> seatsPerRow;

        std::string line;
        std::getline(file, line); // consume rest of the line after seatsPerRow

        while (std::getline(file, line) && !line.empty()) {
            std::istringstream iss(line);
            int startRow, endRow, price;
            char dollarSign;

            while (iss >> startRow >> endRow >> price >> dollarSign) {
                pricePerRowRange[startRow] = price;
                pricePerRowRange[endRow] = price;
            }
        }

        flights.emplace_back(date, flightNumber, seatsPerRow, pricePerRowRange);
    }

    file.close();
    return flights;
}

