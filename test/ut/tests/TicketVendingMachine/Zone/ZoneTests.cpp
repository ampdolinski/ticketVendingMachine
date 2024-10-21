#include <gtest/gtest.h>
#include "TicketVendingMachine/Zone/Zone.hpp"

class ZoneTest : public ::testing::TestWithParam<std::tuple<ZoneType, uint16_t, uint16_t>> {};

INSTANTIATE_TEST_SUITE_P(
    ZoneTests,
    ZoneTest,
    ::testing::Values(
        std::make_tuple(ZoneType::Zone1, 350, 175),
        std::make_tuple(ZoneType::Zone2, 500, 250),
        std::make_tuple(ZoneType::Zone3, 700, 350)
    )
);

TEST_P(ZoneTest, ZonePricesTest) {
    ZoneType zoneType;
    uint16_t fullPrice;
    uint16_t reducedPrice;
    std::tie(zoneType, fullPrice, reducedPrice) = GetParam();

    Zone zone(zoneType);

    ASSERT_EQ(zone.getFullPrice(), fullPrice);
    ASSERT_EQ(zone.getReducedPrice(), reducedPrice);
}
