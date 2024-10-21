#include <iostream>

#include "TicketVendingMachine/Zone/Zone.hpp"
#include "User/Client.hpp"

namespace User
{

Client::Client(std::shared_ptr<IPrinter> printer)
    : printer_(printer) {}

void Client::buyTicket(
    const std::string& zone, const std::string& type, uint16_t price) {
    printer_->printTicket(zone, type, price);
}

void Client::showZones() {
    const auto zones = Zone::createDefaultZones();
    for (const auto& pair : zones) {
        std::cout << pair.second.getZoneName() << ": Full Price = " 
                  << pair.second.getFullPrice() << ", Reduced Price = " 
                  << pair.second.getReducedPrice() << std::endl;
    }
}

} // namespace
