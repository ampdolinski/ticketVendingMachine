#include <iostream>

#include "User/Admin.hpp"
#include "TicketVendingMachine/VendingMachine.hpp"

namespace User
{

Admin::Admin(std::shared_ptr<TicketVendingMachine::VendingMachine> vendingMachine)
    : vendingMachine_(vendingMachine) {}

void Admin::addPaper(uint16_t amountOfNewEmptyTickets) {
    std::cout << "Adding paper to the ticket vending machine..." << std::endl;
    vendingMachine_->addEmptyTicketsAmount(amountOfNewEmptyTickets);
    std::cout << "Actual amount of empty tickets = " << vendingMachine_->getEmptyTicketsAmount() << std::endl;
}

void Admin::addCoins(const std::string& currency, uint16_t denomination, int amount) {
    vendingMachine_->updateDenominationAmount(currency, denomination, amount);
    std::cout << "Added " << amount << " coins of denomination " 
              << denomination << " to " << currency << std::endl;
}

void Admin::terminateProgram() {
    std::cout << "Terminating the ticket vending machine program..." << std::endl;
    vendingMachine_->turnOffMachine();
    // exit(0);
}

}