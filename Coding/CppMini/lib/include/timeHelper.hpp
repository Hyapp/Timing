#include<chrono>
#include <thread>
namespace Hy
{
    class ScopeTimer
    {
        public:
        ScopeTimer();
        ScopeTimer(const ScopeTimer& rhs) = delete;
        ScopeTimer(const ScopeTimer&& rhs) = delete;

        size_t ns() const;
        size_t ms() const;
        size_t s() const;

        void Reset();

        private:
        std::chrono::high_resolution_clock::time_point m_start;
        std::chrono::high_resolution_clock::duration m_duration;
    };
}