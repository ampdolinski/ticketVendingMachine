#include "Utilities/ExceptionHandler.hpp"
#include "Utilities/Logger.hpp"
#include <iostream>

void ExceptionHandler::handle(const std::exception& e) {
    Logger::getInstance().log(std::string("Exception: ") + e.what());
    std::cerr << "An error occurred: " << e.what() << std::endl;
}

void ExceptionHandler::logAndRethrow(const std::string& context, const std::exception& e) {
    std::string message = "Exception in " + context + ": " + e.what();
    Logger::getInstance().log(message);
    throw std::runtime_error(message);
}
