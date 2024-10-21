#pragma once

#include <memory>

// Forward declare VendingMachine class to avoid circular dependency
namespace TicketVendingMachine {
    class VendingMachine;
}

namespace User
{

class Admin
{
public:
    Admin(std::shared_ptr<TicketVendingMachine::VendingMachine> vendingMachine);
    void addPaper(uint16_t amountOfNewEmptyTickets);
    void addCoins(const std::string& currency, uint16_t denomination, int amount);
    void terminateProgram();

private:
    std::shared_ptr<TicketVendingMachine::VendingMachine> vendingMachine_;
};

} // namespace