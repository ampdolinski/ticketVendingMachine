#pragma once

#include <string>
#include <cstdint>

class IPrinter {
public:
    virtual ~IPrinter() = default;
    virtual void printNotification(const std::string& notification) const = 0;
    virtual void printTicket(const std::string& zone, const std::string& type, uint16_t price) const = 0;
};
