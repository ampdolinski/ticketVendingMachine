#include <iostream>

#include "../include/Printer/PrinterConsole.hpp"

void PrinterConsole::printNotification(const std::string& notification) const
{
    std::cout << notification << std::endl;
}

void PrinterConsole::printTicket(const std::string& zone, const std::string& type, uint16_t price) const
{
    std::cout << "Ticket - Zone: " << zone << ", Type: " << type << ", Price: " << price << std::endl;
    // std::cout << "#################" << std::endl;
    // std::cout << "#    Ticket     #" << std::endl;
    // std::cout << "# zone = " << zone << " #" << std::endl;
    // std::cout << "# type = " << type << "   #" << std::endl;
    // std::cout << "# price = " << price << "   #" << std::endl;
    // std::cout << "#################" << std::endl;
}

template <class T>
void PrinterConsole::printNotifications(std::initializer_list<T> list) const
{
    for( auto elem : list )
    {
        printNotification(elem);
    }
}