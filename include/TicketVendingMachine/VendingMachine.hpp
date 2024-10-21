#pragma once

#include <memory>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cstdint>

#include "Currencies/ICurrency.hpp"
#include "Ticket/Ticket.hpp"
#include "User/Admin.hpp"
#include "User/Client.hpp"
#include "Printer/IPrinter.hpp"
#include "Printer/PrinterConsole.hpp"

namespace TicketVendingMachine
{

class VendingMachine
{
public:
    VendingMachine();
    void run();
    void startClientMode();
    void startAdminMode();
    void addCurrency(std::shared_ptr<ICurrency> currency);
    void printCurrencyAmounts(const ICurrency& selectedCurrency);
    void addTickets(const Ticket& ticket, const uint16_t amount);
    void updateDenominationAmount(const std::string& currencyName, uint16_t denomination, int amount);
    void turnOffMachine();
    void setMaxOneTimeTicketAmount(const uint16_t newMaxAmount);
    void addEmptyTicketsAmount(const uint16_t amountToAdd);
    void removeEmptyTicketsAmount(const uint16_t amountToRemove);
    void handleIncomingObjectsFromClient(const ICurrency& selectedCurrency, uint16_t& finalPrice);
    
    // Getters
    const std::vector<Ticket>& getTickets() const;
    const std::map<std::string, std::map<uint16_t, int>>& getDenominationAmounts() const;
    const std::set<std::shared_ptr<ICurrency>>& getCurrencies() const;
    const bool getTurnOffFlag() const;
    const uint16_t getMaxOneTimeTicketAmount() const;
    const uint16_t getEmptyTicketsAmount() const;

private:
    std::set<std::shared_ptr<ICurrency>> currencies_;
    std::vector<Ticket> tickets_;
    std::map<std::string, std::map<uint16_t, int>> denominationAmounts_; // To track denominations and their amounts
    std::shared_ptr<IPrinter> printer_;
    std::unique_ptr<User::Client> client_;
    std::unique_ptr<User::Admin> admin_;
    bool turnOffFlag_ = false;
    uint16_t emptyTicketsAmount_ = 10;  // Initialize amounts to 10
    uint16_t maxOneTimeTicketAmount_ = 20;
};

}
