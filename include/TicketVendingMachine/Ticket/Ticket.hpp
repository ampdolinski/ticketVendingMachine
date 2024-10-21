#pragma once

#include <cstdint>
#include <string>

class Ticket {
public:
    Ticket(const std::string& zone, const std::string& type, uint16_t price);

    std::string getZone() const;
    std::string getType() const;
    uint16_t getPrice() const;

private:
    std::string zone_;
    std::string type_;
    uint16_t price_; // Price in the smallest currency unit (e.g., grosze)
};
