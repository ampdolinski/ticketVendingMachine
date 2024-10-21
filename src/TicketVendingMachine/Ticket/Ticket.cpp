#include "TicketVendingMachine/Ticket/Ticket.hpp"

Ticket::Ticket(const std::string& zone, const std::string& type, uint16_t price)
    : zone_(zone), type_(type), price_(price) {}

std::string Ticket::getZone() const {
    return zone_;
}

std::string Ticket::getType() const {
    return type_;
}

uint16_t Ticket::getPrice() const {
    return price_;
}
