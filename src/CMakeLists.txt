# Add library for core components
add_library(TicketVendingMachine
    TicketVendingMachine/VendingMachine.cpp
    TicketVendingMachine/Currencies/CurrencyPln.cpp
    TicketVendingMachine/Ticket/Ticket.cpp
    TicketVendingMachine/Zone/Zone.cpp
)

# Add library for Printer components
add_library(Printer
    Printer/PrinterConsole.cpp
)

# Add library for User components
add_library(User
    User/Client.cpp
    User/Admin.cpp
)

# Add library for Utility components
add_library(Utilities
    Utilities/Logger.cpp
    Utilities/ExceptionHandler.cpp
)

# Ensure all libraries are linked to the main executable
add_executable(main main.cpp)
target_link_libraries(main
    TicketVendingMachine
    Printer
    User
    Utilities
)

# Add dependency to ensure correct build order
add_dependencies(User TicketVendingMachine)
add_dependencies(Printer TicketVendingMachine)
add_dependencies(Utilities TicketVendingMachine)
add_dependencies(main TicketVendingMachine Printer User Utilities)
