#include "../include/timeHelper.hpp"

namespace Hy
{
    ScopeTimer::ScopeTimer()
    {
        m_start = std::chrono::high_resolution_clock::now();
    }
    
    size_t ScopeTimer::ns() const
    {
        auto dur = std::chrono::high_resolution_clock::now() - m_start;
        return std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
    }

    size_t ScopeTimer::ms() const
    {
        auto dur = std::chrono::high_resolution_clock::now() - m_start;
        return std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    }

    size_t ScopeTimer::s() const
    {
        auto dur = std::chrono::high_resolution_clock::now() - m_start;
        return std::chrono::duration_cast<std::chrono::seconds>(dur).count();
    }

    void ScopeTimer::Reset()
    {
        m_start = std::chrono::high_resolution_clock::now();
    }
}