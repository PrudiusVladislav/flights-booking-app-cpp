cmake_minimum_required(VERSION 3.29)
project(airplane_booking_app)

set(CMAKE_CXX_STANDARD 23)

add_executable(airplane_booking_app main.cpp
        flights/FlightsRepository.cpp
        flights/FlightsRepository.h
        flights/Flight.cpp
        flights/Flight.h
        tickets/Ticket.h
        tickets/TicketsRepository.cpp
        tickets/TicketsRepository.h
        tickets/TicketsService.cpp
        tickets/TicketsService.h
        value-objects/Seat.h
        value-objects/FlightIdentifier.h
        tickets/TicketsApi.cpp
        tickets/TicketsApi.h
        tickets/Ticket.cpp)
