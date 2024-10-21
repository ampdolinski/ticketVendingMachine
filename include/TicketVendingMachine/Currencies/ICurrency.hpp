#pragma once

#include <string>
#include <set>
#include <cstdint>

class ICurrency
{
public:
    virtual ~ICurrency() = default;
    virtual std::string getCurrencyName() const = 0;
    virtual uint16_t getExchangeRate() const = 0;
    virtual std::set<uint16_t> getPaperBanknotes() const = 0;
    virtual std::set<uint16_t> getMainCurrencyCoins() const = 0;
    virtual std::set<uint16_t> getFractionalCoins() const = 0;
    virtual std::string getDenominationName(uint16_t denomination) const = 0;
};