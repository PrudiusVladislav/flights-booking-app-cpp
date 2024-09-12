#include "tickets/TicketsApi.h"
#include "tickets/TicketsService.h"

int main() {
    auto flightsRepository = FlightsRepository("../data/flights.txt");
    auto ticketsRepository = TicketsRepository(&flightsRepository);
    TicketsService ticketsService(&ticketsRepository);
    TicketsApi ticketsApi(&ticketsService);

    ticketsApi.run();
    return 0;
}
