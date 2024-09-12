cmake_minimum_required(VERSION 3.29)
project(airplane_booking_app)

set(CMAKE_CXX_STANDARD 23)

add_executable(airplane_booking_app src/main.cpp
        src/flights/FlightsRepository.cpp
        src/flights/FlightsRepository.h
        src/flights/Flight.cpp
        src/flights/Flight.h
        src/tickets/Ticket.h
        src/tickets/TicketsRepository.cpp
        src/tickets/TicketsRepository.h
        src/tickets/TicketsService.cpp
        src/tickets/TicketsService.h
        src/value-objects/Seat.h
        src/value-objects/FlightIdentifier.h
        src/tickets/TicketsApi.cpp
        src/tickets/TicketsApi.h
        src/tickets/Ticket.cpp)
