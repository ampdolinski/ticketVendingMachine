#pragma once

#include <string>
#include <memory>

#include "Printer/IPrinter.hpp"

namespace User
{

class Client
{
public:
    Client(std::shared_ptr<IPrinter> printer);
    void buyTicket(
        const std::string& zone, const std::string& type, uint16_t price);
    void showZones();

private:
    std::shared_ptr<IPrinter> printer_;
};

} // namespace