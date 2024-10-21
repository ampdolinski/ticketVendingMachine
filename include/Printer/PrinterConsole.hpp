#pragma once

#include "IPrinter.hpp"

class PrinterConsole : public IPrinter {
public:
    void printNotification(const std::string& notification) const override;
    void printTicket(
        const std::string& zone, const std::string& type, uint16_t price) const override;
    
    template <class T>
    void printNotifications(std::initializer_list<T> list) const;
};
