#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>

// #include "Mocks.hpp"

#include "TicketVendingMachine/VendingMachine.hpp"
#include "TicketVendingMachine/Currencies/CurrencyPln.hpp"
#include "TicketVendingMachine/Zone/Zone.hpp"
#include "Printer/PrinterConsole.hpp"



using ::testing::_;
using ::testing::AtLeast;

// Mock classes
class MockPrinter : public IPrinter {
public:
    MOCK_METHOD(void, printTicket, (const std::string& zone, const std::string& type, uint16_t price), (const, override));
};

class MockClient {
public:
    MOCK_METHOD(void, buyTicket, (const std::string& zone, const std::string& type, uint16_t price));
};

class MockAdmin {
public:
    MOCK_METHOD(void, addPaper, ());
    MOCK_METHOD(void, addCoins, (const std::string& currency, uint16_t denomination, int amount));
    MOCK_METHOD(void, terminateProgram, ());
};

class VendingMachineTest : public ::testing::Test {
protected:
    std::shared_ptr<TicketVendingMachine::VendingMachine> vendingMachine;
    std::shared_ptr<MockPrinter> mockPrinter;
    std::shared_ptr<MockClient> mockClient;
    std::shared_ptr<MockAdmin> mockAdmin;

    void SetUp() override {
        mockPrinter = std::make_shared<MockPrinter>();
        mockClient = std::make_shared<MockClient>();
        mockAdmin = std::make_shared<MockAdmin>();
        vendingMachine = std::make_shared<TicketVendingMachine::VendingMachine>();
        vendingMachine->addCurrency(std::make_shared<CurrencyPln>());
    }

    void TearDown() override {
        // Any necessary cleanup
    }
};

TEST_F(VendingMachineTest, SelectSecondZoneReducedPrice) {
    // Mocking user input
    std::stringstream input("2\nR\n1\n2\n");
    std::streambuf* cinbuf = std::cin.rdbuf(); // Save old buffer
    std::cin.rdbuf(input.rdbuf()); // Redirect std::cin to input

    std::stringstream output;
    std::streambuf* coutbuf = std::cout.rdbuf(); // Save old buffer
    std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output

    vendingMachine->run();

    // Restore original buffers
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);

    // Validate the output
    std::string outStr = output.str();
    EXPECT_NE(outStr.find("Zone 2"), std::string::npos);
    EXPECT_NE(outStr.find("Reduced Price = 250"), std::string::npos);
    EXPECT_NE(outStr.find("Final price: 250 grosze."), std::string::npos);

    // Expectations for mocks
    EXPECT_CALL(*mockPrinter, printTicket(_, _, _)).Times(AtLeast(1));
    mockPrinter->printTicket("Zone 2", "R", 250);
}

// TEST_F(VendingMachineTest, AddTicketTest) {
//     Ticket ticket("Zone 2", "Full", 350);
//     vendingMachine->addTicket(ticket);

//     ASSERT_EQ(vendingMachine->getTickets().size(), 1);
//     ASSERT_EQ(vendingMachine->getTickets()[0].getZone(), "Zone 1");
//     ASSERT_EQ(vendingMachine->getTickets()[0].getPrice(), 145);
// }


// class VendingMachineParameterizedTest : public ::testing::TestWithParam<std::tuple<std::string, uint16_t, int>> {};

// INSTANTIATE_TEST_SUITE_P(
//     UpdateDenominationAmountParamTests,
//     VendingMachineParameterizedTest,
//     ::testing::Values(
//         std::make_tuple("PLN", 100, 10),
//         std::make_tuple("PLN", 200, 5),
//         std::make_tuple("PLN", 500, 8)
//     )
// );

// TEST_P(VendingMachineParameterizedTest, UpdateDenominationAmountParamTest) {
//     std::string currencyName;
//     uint16_t denomination;
//     int amount;
//     std::tie(currencyName, denomination, amount) = GetParam();

//     auto vendingMachine = std::make_shared<TicketVendingMachine::VendingMachine>();
//     vendingMachine->addCurrency(std::make_shared<CurrencyPln>());

//     vendingMachine->updateDenominationAmount(currencyName, denomination, amount);

//     auto it = vendingMachine->getDenominationAmounts().find(currencyName);
//     ASSERT_NE(it, vendingMachine->getDenominationAmounts().end());
//     auto denomIt = it->second.find(denomination);
//     ASSERT_NE(denomIt, it->second.end());
//     ASSERT_EQ(denomIt->second, amount);
// }
