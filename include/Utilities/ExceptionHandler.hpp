#pragma once

#include <exception>
#include <string>

class ExceptionHandler {
public:
    static void handle(const std::exception& e);
    static void logAndRethrow(const std::string& context, const std::exception& e);
};
