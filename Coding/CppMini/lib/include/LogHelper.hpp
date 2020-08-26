#pragma once
#include <iostream>
#include <string>

namespace LogHelper
{
    void LogClear();

    void LogLine(const std::string& context, std::ostream& os = std::cout);

    void LogSpaceLine(const size_t counter = 1, std::ostream &os = std::cout);
} // namespace LogHelper
