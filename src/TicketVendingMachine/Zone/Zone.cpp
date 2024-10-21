#include "TicketVendingMachine/Zone/Zone.hpp"

Zone::Zone(ZoneType zoneType)
    : zoneType_(zoneType),
    fullPrice_(static_cast<uint16_t>(zoneType)),
    reducedPrice_(fullPrice_ / 2) {}

ZoneType Zone::getZoneType() const {
    return zoneType_;
}

std::string Zone::getZoneName() const {
    return zoneTypeToString(zoneType_);
}

uint16_t Zone::getFullPrice() const {
    return fullPrice_;
}

uint16_t Zone::getReducedPrice() const {
    return reducedPrice_;
}

std::map<ZoneType, Zone> Zone::createDefaultZones() {
    std::map<ZoneType, Zone> zones;
    zones[ZoneType::Zone1] = Zone(ZoneType::Zone1);
    zones[ZoneType::Zone2] = Zone(ZoneType::Zone2);
    zones[ZoneType::Zone3] = Zone(ZoneType::Zone3);
    return zones;
}

std::string Zone::zoneTypeToString(ZoneType zoneType) const {
    switch (zoneType) {
        case ZoneType::Zone1: return "Zone 1";
        case ZoneType::Zone2: return "Zone 2";
        case ZoneType::Zone3: return "Zone 3";
        default: return "Unknown Zone";
    }
}
