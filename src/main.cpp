#include <iostream>

#include "TicketVendingMachine/VendingMachine.hpp"

int main()
{
    // Create an instance of the VendingMachine
    std::shared_ptr<TicketVendingMachine::VendingMachine> vendingMachine = std::make_shared<TicketVendingMachine::VendingMachine>();

    // Run the vending machine in loop to simulate continuous operation,
    // until Admin will TURN OFF Machine
    while (!vendingMachine->getTurnOffFlag()) {
        vendingMachine->run();
    }

    return 0;
}