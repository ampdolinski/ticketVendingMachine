#include "TicketVendingMachine/Currencies/CurrencyPln.hpp"

std::string CurrencyPln::getCurrencyName() const {
    return currencyName_;
}

uint16_t CurrencyPln::getExchangeRate() const {
    return exchangeRate_;
}

std::set<uint16_t> CurrencyPln::getPaperBanknotes() const {
    return paperBanknotes_;
}

std::set<uint16_t> CurrencyPln::getMainCurrencyCoins() const {
    return mainCurrencyCoins_;
}

std::set<uint16_t> CurrencyPln::getFractionalCoins() const {
    return fractionalCoins_;
}
