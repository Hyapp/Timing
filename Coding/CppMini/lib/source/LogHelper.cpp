#include "LogHelper.hpp"

#include<cstring>

namespace LogHelper
{
    void LogLine(const std::string &context, std::ostream &os)
    {
        os << context << "\n";
    }

    void LogSpaceLine(const size_t counter, std::ostream &os)
    {
        if (counter == 0)
        {
            return;
        }
        
        char buffer[counter + 1];
        std::memset(buffer, static_cast<int>('\n'), counter + 1);
        buffer[counter] = '\0';
        
        os << buffer;
        
        return;
    }

    void LogClear()
    {
        system("clear");
    }
}