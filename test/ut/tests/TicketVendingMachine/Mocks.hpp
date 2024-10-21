#pragma once

#include <gmock/gmock.h>

#include "Printer/IPrinter.hpp"
#include "User/Client.hpp"
#include "User/Admin.hpp"

class MockPrinter : public IPrinter {
public:
    MOCK_METHOD(void, printTicket, (const std::string& zone, const std::string& type, uint16_t price), (const, override));
};

class MockClient : public User::Client {
public:
    MockClient(std::shared_ptr<IPrinter> printer) : User::Client(printer) {}
    MOCK_METHOD(void, buyTicket, (const std::string& zone, const std::string& type, uint16_t price), ());
    MOCK_METHOD(void, showZones, (), ());
};

class MockAdmin : public User::Admin {
public:
    MockAdmin(std::shared_ptr<TicketVendingMachine::VendingMachine> vendingMachine) : User::Admin(vendingMachine) {}
    MOCK_METHOD(void, addPaper, (), ());
    MOCK_METHOD(void, addCoins, (const std::string& currency, uint16_t denomination, int amount), ());
    MOCK_METHOD(void, terminateProgram, (), ());
};
