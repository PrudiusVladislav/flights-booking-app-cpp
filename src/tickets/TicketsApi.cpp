//
// Created by Vladyslav Prudius  on 10.09.2024.
//

#include "TicketsApi.h"

#include <iostream>
#include <sstream>

TicketsApi::TicketsApi(TicketsService* ticketsService) : _ticketsService(ticketsService) {
    _commandHandlers["check"] = [this](std::istringstream& iss) { handleCheck(iss); };
    _commandHandlers["book"] = [this](std::istringstream& iss) { handleBook(iss); };
    _commandHandlers["return"] = [this](std::istringstream& iss) { handleReturn(iss); };
    _commandHandlers["view"] = [this](std::istringstream& iss) { handleView(iss); };
}

void TicketsApi::processCommand(const std::string& command) {
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;

    auto it = _commandHandlers.find(cmd);
    if (it != _commandHandlers.end()) {
        it->second(iss);
    } else {
        std::cout << "Unknown command\n";
    }
}

void TicketsApi::handleCheck(std::istringstream& iss) {
    std::string date, flightNumber;
    iss >> date >> flightNumber;
    if (!validateDateAndFlightNumber(date, flightNumber)) {
        std::cout << "Invalid date or flight number\n";
        return;
    }
    checkAvailability(date, flightNumber);
}

void TicketsApi::handleBook(std::istringstream& iss) {
    std::string date, flightNumber, seat, username;
    iss >> date >> flightNumber >> seat >> username;
    if (!validateBookingDetails(date, flightNumber, seat, username)) {
        std::cout << "Invalid booking details\n";
        return;
    }
    bookTicket(date, flightNumber, seat, username);
}

void TicketsApi::handleReturn(std::istringstream& iss) {
    int id;
    iss >> id;
    if (!validateTicketId(id)) {
        std::cout << "Invalid ticket ID\n";
        return;
    }
    returnTicket(id);
}

void TicketsApi::handleView(std::istringstream& iss) {
    std::string identifier;
    iss >> identifier;

    if (std::ranges::all_of(identifier, ::isdigit)) {
        int id = std::stoi(identifier);
        if (!validateTicketId(id)) {
            std::cout << "Invalid ticket ID\n";
            return;
        }
        viewById(id);
    } else if (identifier == "username") {
        std::string username;
        iss >> username;
        if (username.empty()) {
            std::cout << "Invalid username\n";
            return;
        }
        viewByUsername(username);
    } else if (identifier == "flight") {
        std::string date, flightNumber;
        iss >> date >> flightNumber;
        if (!validateDateAndFlightNumber(date, flightNumber)) {
            std::cout << "Invalid date or flight number\n";
            return;
        }
        viewFlight(date, flightNumber);
    } else {
        std::cout << "Unknown view command\n";
    }
}


bool TicketsApi::validateDateAndFlightNumber(const std::string& date, const std::string& flightNumber) {
    return !date.empty() && !flightNumber.empty();
}

bool TicketsApi::validateBookingDetails(const std::string& date, const std::string& flightNumber, const std::string& seat, const std::string& username) {
    return !date.empty() && !flightNumber.empty() && !seat.empty() && !username.empty();
}

bool TicketsApi::validateTicketId(int id) {
    return id > 0;
}

void TicketsApi::run() {
    _running = true;
    std::string command;
    while (_running) {
        std::cout << "Enter command: ";
        std::getline(std::cin, command);
        if (command == "exit") {
            _running = false;
            break;
        }
        processCommand(command);
    }
}

void TicketsApi::checkAvailability(const std::string& date, const std::string& flightNumber) {
    FlightIdentifier identifier{date, flightNumber};
    std::vector<std::shared_ptr<Ticket>> availableTickets = _ticketsService->viewAvailable(identifier);
    for (const std::shared_ptr<Ticket>& ticket : availableTickets) {
        std::cout << "> " << ticket->getSeat().toString() << " " << ticket->getPrice() << "$" << std::endl;
    }
}

void TicketsApi::bookTicket(
    const std::string& date,
    const std::string& flightNumber,
    const std::string& seat,
    const std::string& username)
{
    const Seat seatValue{seat};
    const BookingRequest request{username, date, flightNumber, seatValue};
    try {
        const int ticketId = _ticketsService->book(request);
        std::cout << "Confirmed with ID " << ticketId << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void TicketsApi::returnTicket(int ticketId) {
    try {
        _ticketsService->returnWithRefund(ticketId);
        std::cout << "Confirmed refund for ticket ID " << ticketId << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void TicketsApi::viewById(const int ticketId) {
    const std::shared_ptr<Ticket> ticket = _ticketsService->view(ticketId);
    if (!ticket) {
        std::cout << "Ticket not found" << std::endl;
        return;
    }

    printTicket(*ticket, true);
}

void TicketsApi::viewByUsername(const std::string& username) {
    std::vector<std::shared_ptr<Ticket>> tickets = _ticketsService->viewForUser(username);
    std::cout << "Tickets for " << username << std::endl;
    for (const std::shared_ptr<Ticket>& ticket : tickets) {
        printTicket(*ticket, false);
    }
}

void TicketsApi::viewFlight(const std::string& date, const std::string& flightNumber) {
    FlightIdentifier identifier{date, flightNumber};
    std::vector<std::shared_ptr<Ticket>> bookedTickets = _ticketsService->viewBooked(identifier);
    for (const std::shared_ptr<Ticket>& ticket : bookedTickets) {
        std::cout << "> " << ticket->getSeat().toString() << " "
            << ticket->getUsername() << " " << ticket->getPrice() << "$" << std::endl;
    }
}

void TicketsApi::printTicket(const Ticket& ticket, const bool showUsername) {
    std::cout << "> " << ticket.getFlight().getFlightNumber() << ", " << ticket.getFlight().getDate()
        << " seat " << ticket.getSeat().getRow() << ticket.getSeat().getSeatLetter()
        << ", price " << ticket.getPrice() << "$"
        << (showUsername ? ", " + ticket.getUsername() : "") << std::endl;
}