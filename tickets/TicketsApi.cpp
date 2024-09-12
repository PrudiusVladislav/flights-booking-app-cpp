//
// Created by Vladyslav Prudius  on 10.09.2024.
//

#include "TicketsApi.h"

#include <iostream>
#include <sstream>

void TicketsApi::processCommand(const std::string &command) {
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;

    if (cmd == "check") {
        std::string date, flightNumber;
        iss >> date >> flightNumber;
        checkAvailability(date, flightNumber);
    } else if (cmd == "book") {
        std::string date, flightNumber, seat, username;
        iss >> date >> flightNumber >> seat >> username;
        bookTicket(date, flightNumber, seat, username);
    } else if (cmd == "return") {
        int id;
        iss >> id;
        returnTicket(id);
    } else if (cmd == "view") {
        std::string identifier;
        iss >> identifier;

        if (std::ranges::all_of(identifier, ::isdigit)) {
            viewById(std::stoi(identifier));
        } else if (identifier == "username") {
            std::string username;
            iss >> username;
            viewByUsername(username);
        } else if (identifier == "flight") {
            std::string date, flightNumber;
            iss >> date >> flightNumber;
            viewFlight(date, flightNumber);
        } else {
            std::cout << "Unknown view command\n";
        }
    } else {
        std::cout << "Unknown command\n";
    }
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

void printTicket(const Ticket& ticket, const bool showUsername) {
    std::cout << "> " << ticket.getFlight().getFlightNumber() << ", " << ticket.getFlight().getDate()
        << " seat " << ticket.getSeat().getRow() << ticket.getSeat().getSeatLetter()
        << ", price " << ticket.getPrice() << "$"
        << (showUsername ? ", " + ticket.getUsername() : "") << std::endl;
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