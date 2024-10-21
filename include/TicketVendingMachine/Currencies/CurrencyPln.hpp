#pragma once

#include <map>
#include <set>

#include "ICurrency.hpp"
#include "DenominationPln.hpp"

class CurrencyPln : public ICurrency
{
public:
    std::string getCurrencyName() const override;
    uint16_t getExchangeRate() const override;
    std::set<uint16_t> getPaperBanknotes() const override;
    std::set<uint16_t> getMainCurrencyCoins() const override;
    std::set<uint16_t> getFractionalCoins() const override;
    std::string getDenominationName(uint16_t denomination) const override {
        static const std::map<DenominationPln, std::string> denominationNames = {
            {DenominationPln::Grosze1, "1gr"},
            {DenominationPln::Grosze2, "2gr"},
            {DenominationPln::Grosze5, "5gr"},
            {DenominationPln::Grosze10, "10gr"},
            {DenominationPln::Grosze20, "20gr"},
            {DenominationPln::Grosze50, "50gr"},
            {DenominationPln::PLN1, "1PLN"},
            {DenominationPln::PLN2, "2PLN"},
            {DenominationPln::PLN5, "5PLN"},
            {DenominationPln::PLN10, "10PLN"},
            {DenominationPln::PLN20, "20PLN"},
            {DenominationPln::PLN50, "50PLN"},
            {DenominationPln::PLN100, "100PLN"},
            {DenominationPln::PLN200, "200PLN"},
        };

        auto it = denominationNames.find(static_cast<DenominationPln>(denomination));
        return it != denominationNames.end() ? it->second : "Unknown Denomination";
    };
    

private:
    const std::string currencyName_ = "PLN";
    const uint16_t exchangeRate_ = 100; // 1 PLN = 100 grosze
    const std::set<uint16_t> paperBanknotes_ = {
        static_cast<uint16_t>(DenominationPln::PLN10),
        static_cast<uint16_t>(DenominationPln::PLN20),
        static_cast<uint16_t>(DenominationPln::PLN50),
        static_cast<uint16_t>(DenominationPln::PLN100),
        static_cast<uint16_t>(DenominationPln::PLN200)};
    const std::set<uint16_t> mainCurrencyCoins_ = {
        static_cast<uint16_t>(DenominationPln::PLN1),
        static_cast<uint16_t>(DenominationPln::PLN2),
        static_cast<uint16_t>(DenominationPln::PLN5)};
    const std::set<uint16_t> fractionalCoins_ = {
        static_cast<uint16_t>(DenominationPln::Grosze1),
        static_cast<uint16_t>(DenominationPln::Grosze2),
        static_cast<uint16_t>(DenominationPln::Grosze5),
        static_cast<uint16_t>(DenominationPln::Grosze10),
        static_cast<uint16_t>(DenominationPln::Grosze20),
        static_cast<uint16_t>(DenominationPln::Grosze50)
    };
};
