#include <iostream>
#include <string>
#include <algorithm>

#include "TicketVendingMachine/VendingMachine.hpp"
#include "TicketVendingMachine/Currencies/CurrencyPln.hpp"
#include "TicketVendingMachine/Zone/Zone.hpp"
#include "Printer/PrinterConsole.hpp"
#include "Utilities/Logger.hpp"

namespace TicketVendingMachine {

namespace
{
uint16_t calculateTotalPrice(const std::vector<Ticket>& tickets)
{
    uint16_t totalPrice = 0;
    for (const auto& ticket : tickets) {
        totalPrice += ticket.getPrice();
    }
    return totalPrice;
}

std::string printPrice(const uint16_t totalPrice)
{
    std::string numStr = std::to_string(totalPrice);
    
    // Split the string as required (assuming number has at least two digits)
    if (numStr.length() > 2)
    {
        uint16_t strLength = numStr.size();
        return numStr.substr(0, strLength - 2) + "," + numStr.substr(strLength - 2, 2) + " PLN";
    }
    else if (numStr.length() == 2)
    {
        return "0," + numStr + " PLN";
    }
    else
    {
        return "0,0" + numStr + " PLN";
    }
}

} // namespace

VendingMachine::VendingMachine() {
    printer_ = std::make_shared<PrinterConsole>();
    client_ = std::make_unique<User::Client>(printer_);
    admin_ = std::make_unique<User::Admin>(std::shared_ptr<VendingMachine>(this));
    // Logger::log("Vending Machine initialized.");

}

void VendingMachine::run()
{
    // Logger::log("Vending Machine started.");
    printer_->printNotification("Welcome to the Ticket Vending Machine!");
    printer_->printNotification("WARNING! Machine doesn't return change at this moment.");

    startClientMode();
}

void VendingMachine::startClientMode()
{
    addCurrency(std::make_shared<CurrencyPln>());
    std::map<ZoneType, Zone> zones = Zone::createDefaultZones();
    while (true) {
        std::map<int, Zone> zonesIterator;
        int zoneNumber = 1;
        printer_->printNotification(("Available Zones and Prices:"));
        for (const auto& pair : zones) {
            std::cout << zoneNumber << ". " << pair.second.getZoneName() 
                      << ": Full Price = " << printPrice(pair.second.getFullPrice()) 
                      << ", Reduced Price = " << printPrice(pair.second.getReducedPrice()) << std::endl;
            zonesIterator[zoneNumber] = pair.second;
            zoneNumber++;
        }

        std::string inputString;
        uint32_t inputNumberOnly;
        std::cout << "Enter the number of the zone you choose: ";
        std::cin >> inputNumberOnly;

        if (inputNumberOnly == 123456) {
            printer_->printNotification("Switching to admin interface...");
            startAdminMode();
            continue;
        }

        while (zonesIterator.find(inputNumberOnly) == zonesIterator.end())
        {
            std::cout << "Only ";
            for (const auto& [zoneNumber, _] : zonesIterator)
            {
                std::cout << "(" << zoneNumber << ") ";
            }
            std::cout << " to select =  ";
            std::cin >> inputNumberOnly;
        }

        while (inputNumberOnly > zonesIterator.size())
        {
            printer_->printNotification("Invalid zone selected.");
            std::cin >> inputNumberOnly;
        }
    
        auto zone = zonesIterator[inputNumberOnly];
        
        std::cout << "Enter 'F' for full price or 'R' for reduced price = ";
        std::cin >> inputString;
        while (inputString != "F" && inputString != "R")
        {
            printer_->printNotification("Only 'F' or 'R' to select =  ");
            std::cin >> inputString;
        }

        std::string ticketType = inputString;
        Zone selectedZone = zone;
    
        uint16_t price = (ticketType == "F") ? selectedZone.getFullPrice() : selectedZone.getReducedPrice();
        std::cout << "The price for your ticket is = " << printPrice(price) << std::endl;

        printer_->printNotification("Enter the number of tickets you want = ");
        std::cin >> inputNumberOnly;
        while (inputNumberOnly + tickets_.size() > getMaxOneTimeTicketAmount())
        {
            std::cout << "This amount exeeds max amount of tickets to collect in one transaction for = "
            << (inputNumberOnly + tickets_.size() - getMaxOneTimeTicketAmount()) <<" tickets." << std::endl;
            std::cout << "You still can buy only = " << (getMaxOneTimeTicketAmount() - tickets_.size()) << " tickets." << std::endl;
            std::cin >> inputNumberOnly;
        }
        while (inputNumberOnly + tickets_.size() > getEmptyTicketsAmount())
        {
            std::cout << "This amount exeeds max amount of tickets possible to print now for:  "
            << (inputNumberOnly + tickets_.size() - getEmptyTicketsAmount()) <<" tickets." << std::endl;
            std::cout << "You still can buy only = " << (getEmptyTicketsAmount() - tickets_.size()) << " tickets." << std::endl;
            std::cin >> inputNumberOnly;
        }

        uint16_t quantity = inputNumberOnly;
        uint16_t totalPrice = price * quantity;
        std::cout << "The price for " << quantity << " ticket(s) = " << printPrice(totalPrice) << std::endl;

        addTickets(Ticket(selectedZone.getZoneName(), ticketType, price), quantity);

        if (tickets_.size() == getMaxOneTimeTicketAmount() || getEmptyTicketsAmount() == 0)
        {
            printer_->printNotification("Not possible to add more tickets. Finalize transaction.");
            break;
        }
        printer_->printNotification("Options:"
            "\n1. Add new ticket"
            "\n2. End selection and proceed to payment"
            "\nChoose an option: ");
        std::cin >> inputNumberOnly;

        if (inputNumberOnly == 2) {
            break;
        }
    }

    uint16_t calculatedFinalPrice = calculateTotalPrice(tickets_);

    std::cout << "Final price: " << printPrice(calculatedFinalPrice) << std::endl;

    handleIncomingObjectsFromClient(CurrencyPln(), calculatedFinalPrice);

    for (const auto& ticket : tickets_) {
        printer_->printTicket(ticket.getZone(), ticket.getType(), ticket.getPrice());
    }
    tickets_.clear();
}

void VendingMachine::startAdminMode()
{
    uint32_t inputNumberOnly;
    printer_->printNotification("Options:"
        "\n1. Add coins/paper banknotes"
        "\n2. Check amounts of available coins/paper banknotes"
        "\n3. Add empty tickets"
        "\n4. Check amounts of available empty tickets"
        "\n5. Change max ticket amount per one transaction"
        "\n6. Switch off machine (TEMP unavailable)"
        "\n7. Return to CLIENT mode"
        "\nChoose an option: ");
    std::cin >> inputNumberOnly;

    while (inputNumberOnly > 0 && inputNumberOnly < 6)
    {
        switch (inputNumberOnly)
        {
            case 1: admin_->addCoins("PLN", static_cast<uint16_t>(DenominationPln::PLN10), 12); break;
            case 2: printCurrencyAmounts(CurrencyPln()); break;
            case 3: admin_->addPaper(25); break;
            case 4: getEmptyTicketsAmount(); break;
            case 5: setMaxOneTimeTicketAmount(30); break;
            // case 6: admin_->terminateProgram(); break;
            case 7: printer_->printNotification("Returning to CLIENT mode"); break;
            default:
                printer_->printNotification("Incorrect option.");
        }
        std::cin >> inputNumberOnly;
    }
    printer_->printNotification("End of ADMIN mode.");
}

// By default, Machine should be equiped in 10 coins / banknotes
// for each possibility in specific currency
void VendingMachine::addCurrency(std::shared_ptr<ICurrency> currency)
{
    currencies_.insert(currency);
    auto currencyName = currency->getCurrencyName();
    std::cout << "Added currency: " << currencyName << std::endl;

    for (auto denom : currency->getPaperBanknotes()) {
        denominationAmounts_[currencyName][denom] = 10; // Initialize amounts to 10
    }

    for (auto denom : currency->getMainCurrencyCoins()) {
        denominationAmounts_[currencyName][denom] = 10; // Initialize amounts to 10
    }

    for (auto denom : currency->getFractionalCoins()) {
        denominationAmounts_[currencyName][denom] = 10; // Initialize amounts to 10
    }
}

void VendingMachine::printCurrencyAmounts(const ICurrency& selectedCurrency)
{
    auto currencyIt = std::find_if(currencies_.begin(), currencies_.end(),
        [&selectedCurrency](const std::shared_ptr<ICurrency>& currency) {
            return selectedCurrency.getCurrencyName() == currency->getCurrencyName();
        }
    );

    if (currencyIt == currencies_.end())
    {
        std::cout << "Not found selected currency = " << selectedCurrency.getCurrencyName() << std::endl;
        return;
    }

    auto selectedCurrencyName = currencyIt->get()->getCurrencyName();

    std::cout << "For selected currency = " << selectedCurrency.getCurrencyName() << " machine contains:" << std::endl;
    std::cout << "- paper bankotes = " << std::endl;
    for (auto denom : currencyIt->get()->getPaperBanknotes()) {
        std::cout << "  - banknote = " << denom << " -> " << denominationAmounts_[selectedCurrencyName][denom] << std::endl;
    }

    for (auto denom : currencyIt->get()->getMainCurrencyCoins()) {
        std::cout << "  - main coin = " << denom << " -> " << denominationAmounts_[selectedCurrencyName][denom] << std::endl;
    }

    for (auto denom : currencyIt->get()->getFractionalCoins()) {
        std::cout << "  - fractianal coin = " << denom << " -> " << denominationAmounts_[selectedCurrencyName][denom] << std::endl;
    }
}

void VendingMachine::addTickets(const Ticket& ticket, const uint16_t amount)
{
    tickets_.insert(tickets_.end(), amount, ticket);
    removeEmptyTicketsAmount(amount);
}

void VendingMachine::updateDenominationAmount(const std::string& currencyName, uint16_t denomination, int amount)
{
    denominationAmounts_[currencyName][denomination] += amount;
}

const std::vector<Ticket>& VendingMachine::getTickets() const
{
    return tickets_;
}

const std::map<std::string, std::map<uint16_t, int>>& VendingMachine::getDenominationAmounts() const
{
    return denominationAmounts_;
}

const std::set<std::shared_ptr<ICurrency>>& VendingMachine::getCurrencies() const
{
    return currencies_;
}

const bool VendingMachine::getTurnOffFlag() const
{
    return turnOffFlag_;
}

void VendingMachine::turnOffMachine()
{
    turnOffFlag_ = true;
}

const uint16_t VendingMachine::getMaxOneTimeTicketAmount() const
{
    return maxOneTimeTicketAmount_;
}

void VendingMachine::setMaxOneTimeTicketAmount(uint16_t newMaxAmount)
{
    maxOneTimeTicketAmount_ = newMaxAmount;
}

const uint16_t VendingMachine::getEmptyTicketsAmount() const
{
    return emptyTicketsAmount_;
}

void VendingMachine::addEmptyTicketsAmount(const uint16_t amountToAdd)
{
    emptyTicketsAmount_ += amountToAdd;
}

void VendingMachine::removeEmptyTicketsAmount(const uint16_t amountToRemove)
{
    emptyTicketsAmount_ -= amountToRemove;
}

void VendingMachine::handleIncomingObjectsFromClient(const ICurrency& selectedCurrency, uint16_t& finalPrice)
{
    auto currencyIt = std::find_if(currencies_.begin(), currencies_.end(),
        [&selectedCurrency](const std::shared_ptr<ICurrency>& currency) {
            return selectedCurrency.getCurrencyName() == currency->getCurrencyName();
        }
    );

    if (currencyIt == currencies_.end())
    {
        std::cout << "Not found selected currency = " << selectedCurrency.getCurrencyName() << std::endl;
        return;
    }

    auto selectedCurrencyName = currencyIt->get()->getCurrencyName();

    std::cout << "Put money one by one into machine:"
        << "\n<write what coin / banknote / something else you try to insert>"
        << "\n<e.g.'50gr', '2PLN', '20PLN', 'kamien'>" << std::endl;
    
    uint16_t toReturn = 0;

    while (finalPrice > 0)
    {
        std::string inputString;
        std::cin >> inputString;

        // WARNING
        // Problem with iteration using lambda - infinite loop
        // potenatial improvement
        // This is the reason to stay with not-nice-looking for loops
    
        // auto checkIfIncomingObjectIsCorrectCoinOrBanknote = [&inputString, &selectedCurrency](const auto& denomination) {
        //     return selectedCurrency.getDenominationName(static_cast<uint16_t>(denomination)) == inputString;
        // };

        uint16_t valueOfInsertedObject = 0;

        for (const auto& paperBankote : currencyIt->get()->getPaperBanknotes())
        {
            if (selectedCurrency.getDenominationName(paperBankote) == inputString)
            {
                valueOfInsertedObject = paperBankote;
            }
        }
        for (const auto& mainCurrencyCoin : currencyIt->get()->getMainCurrencyCoins())
        {
            if (selectedCurrency.getDenominationName(mainCurrencyCoin) == inputString)
            {
                valueOfInsertedObject = mainCurrencyCoin;
            }
        }
        for (const auto& fractionalCoin : currencyIt->get()->getFractionalCoins())
        {
            if (selectedCurrency.getDenominationName(fractionalCoin) == inputString)
            {
                valueOfInsertedObject = fractionalCoin;
            }
        }

        if (valueOfInsertedObject == 0)
        {
            printer_->printNotification("Incorrect object - put only correct coins or banknotes.");
            continue;
        }

        if (finalPrice > valueOfInsertedObject)
        {
            finalPrice -= valueOfInsertedObject;
        }
        else
        {
            toReturn = valueOfInsertedObject - finalPrice;
            finalPrice = 0;
        }

        denominationAmounts_[selectedCurrencyName][valueOfInsertedObject]++;

        // auto objectGetterInPaperBanknotes = std::find_if(
        //     currencyIt->get()->getPaperBanknotes().begin(),
        //     currencyIt->get()->getPaperBanknotes().end(),
        //     checkIfIncomingObjectIsCorrectCoinOrBanknote
        // );
        // auto objectGetterInMainCurrencyCoins = std::find_if(
        //     currencyIt->get()->getMainCurrencyCoins().begin(),
        //     currencyIt->get()->getMainCurrencyCoins().end(),
        //     checkIfIncomingObjectIsCorrectCoinOrBanknote
        // );
        // auto objectGetterInFractionalCoins = std::find_if(
        //     currencyIt->get()->getFractionalCoins().begin(),
        //     currencyIt->get()->getFractionalCoins().end(),
        //     checkIfIncomingObjectIsCorrectCoinOrBanknote
        // );
        //
        // if (objectGetterInPaperBanknotes != currencyIt->get()->getPaperBanknotes().end())
        // {
        //     uint16_t denominationValue = static_cast<uint16_t>(*objectGetterInPaperBanknotes);
        //     if (finalPrice > denominationValue) {
        //         finalPrice -= denominationValue;
        //     } else {
        //         toReturn = denominationValue - finalPrice;
        //         finalPrice = 0;
        //     }
        //     denominationAmounts_[selectedCurrencyName][denominationValue]++;
        // }
        // else if (objectGetterInMainCurrencyCoins != currencyIt->get()->getMainCurrencyCoins().end())
        // {
        //     uint16_t denominationValue = static_cast<uint16_t>(*objectGetterInMainCurrencyCoins);
        //     if (finalPrice > denominationValue) {
        //         finalPrice -= denominationValue;
        //     } else {
        //         toReturn = denominationValue - finalPrice;
        //         finalPrice = 0;
        //     }
        //     denominationAmounts_[selectedCurrencyName][denominationValue]++;
        // }
        // else if (objectGetterInFractionalCoins != currencyIt->get()->getFractionalCoins().end())
        // {
        //     uint16_t denominationValue = static_cast<uint16_t>(*objectGetterInFractionalCoins);
        //     if (finalPrice > denominationValue) {
        //         finalPrice -= denominationValue;
        //     } else {
        //         toReturn = denominationValue - finalPrice;
        //         finalPrice = 0;
        //     }
        //     denominationAmounts_[selectedCurrencyName][denominationValue]++;
        // }
        // else
        // {
        //     printer_->printNotification("Incorrect object - put only correct coins or banknotes.");
        // }

        std::cout << "Still to pay = " << printPrice(finalPrice) << std::endl;
    }

    std::cout << "To return (ask MPK to return money) = " << printPrice(toReturn) << std::endl;

    // TODO
    // hanleReturnChange(toReturn);
}

} // namespace
