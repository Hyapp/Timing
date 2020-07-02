#include"timeHelper.hpp"
#include<iostream>

int main()
{
    Hy::ScopeTimer timer;
    for (size_t i = 0; i < 100; i++)
    {
        std::cout << i << std::endl;
    }
    std::cout << "time : ns : " << timer.ns() << std::endl;
}