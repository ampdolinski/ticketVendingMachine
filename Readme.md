# Ticket Vending Machine

## Project Description
This project implements a ticket vending machine in C++20,
following SOLID principles and using design patterns. The vending machine is designed
to be easily extendable for future use with different currencies.

## Features
- Accepts one currency PLN
- Allows purchasing multiple tickets at once
- Provides change using the largest available denominations
- Separate interfaces for client and admin
- Console-based interface with potential for future GUI expansion
.. - Includes unit tests for core functionalities

## Currency Denominations
### PLN (Polish Złoty)
- **Paper Banknotes**: 10 PLN, 20 PLN, 50 PLN, 100 PLN, 200 PLN
- **Main Currency Coins**: 1 PLN, 2 PLN, 5 PLN
- **Fractional Coins**: 1 Grosz, 2 Grosze, 5 Groszy, 10 Groszy, 20 Groszy, 50 Groszy

## Project Structure
ticket_vending_machine/
│
├── CMakeLists.txt
├── README.md
├── include/
│   ├── TicketVendingMachine/
│       ├── VendingMachine.hpp
│       ├── Currency/
│           ├── Currency.hpp
│           ├── CurrencyPln.hpp
│           ├── DenominationPln.hpp
│       ├── Ticket/
│           ├── Ticket.hpp
│       ├── Zone/
│           ├── Zone.hpp
│   ├── User/
│       ├── Client.hpp
│       ├── Admin.hpp
│   ├── Utilities/
│       ├── Logger.hpp
│       ├── ExceptionHandler.hpp
├── src/
│   ├── main.cpp
│   ├── TicketVendingMachine/
│       ├── VendingMachine.cpp
│       ├── Currency/
│           ├── Currency.cpp
│           ├── CurrencyPln.cpp
│       ├── Ticket/
│           ├── Ticket.cpp
│       ├── Zone/
│           ├── Zone.cpp
│   ├── User/
│       ├── Client.cpp
│       ├── Admin.cpp
│   ├── Utilities/
│       ├── Logger.cpp
│       ├── ExceptionHandler.cpp
│   ├── Tests/
│       ├── VendingMachineTests.cpp
│       ├── CurrencyTests.cpp
│       ├── TicketTests.cpp
│       ├── ZoneTests.cpp
│       ├── UserTests.cpp
│       ├── UtilitiesTests.cpp


## Building the Project
1. **Clone the repository:**

   git clone <repository-url>
   cd ticketVendingMachine

2. **Build with CMake:**

    mkdir build
    cd build
    cmake -G "MinGW Makefiles" ..
    mingw32-make

3. **Running the Project
After building, you can run the executable:**

    ./main.exe

<!-- @TODO Activate tests -->
<!-- 4. **Running Tests
Unit tests are included and can be run using CMake's testing support:**

    cd build
    make test -->

<!-- 5. **Generowanie Raportu Pokrycia
Po uruchomieniu testów:**

    make coverage

    Raport pokrycia znajdziesz w pliku coverage/index.html. -->


Future Improvements
- Integrate a GUI interface.
- Extend support for additional currencies.
- Add more comprehensive error handling and logging.
- Send email when low amount of banknotes / coins / empty tickets
- Store in memory amounts of all money inside machine (later could be changed into additional input from sensor for stored money, to be independend from stored values)
