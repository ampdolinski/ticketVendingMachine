#pragma once

#include <string>
#include <map>
#include <cstdint>

// Full price in grosze
enum class ZoneType : uint16_t {
    Zone1 = 350, 
    Zone2 = 500,
    Zone3 = 700,
};

// enum class ZoneType {
//     Zone1, 
//     Zone2,
//     Zone3,
// };

class Zone
{
public:
    Zone() = default; 
    Zone(ZoneType zoneType);

    ZoneType getZoneType() const;
    std::string getZoneName() const;
    uint16_t getFullPrice() const;
    uint16_t getReducedPrice() const;

    // Factory method to create sample zones
    static std::map<ZoneType, Zone> createDefaultZones(); 
    std::string zoneTypeToString(ZoneType zoneType) const;

private:
    ZoneType zoneType_;
    uint16_t fullPrice_;
    uint16_t reducedPrice_;
    
};
