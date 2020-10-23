#include "../include/LeetCode.hpp"
#include "../../lib/include/timeHelper.hpp"
using namespace Hy;


#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <random>


namespace LeetCode
{
    void Test001()
    {
        constexpr int x[] = 
        {
            1,2,3,4,5,6,7,8,9            
        };
        constexpr int target = 11;
        size_t idx0, idx1;
        std::vector<int> targets;
        std::mt19937 seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> randomG(1, 20);
        for(size_t i = 0; i < 10000; ++i)
        {
            targets.push_back(randomG(seed));
        }


        {
            ScopeTimer st;
            for (const auto i : targets)
            {
                Func001_For(x, sizeof(x)/ sizeof(int), i, idx0, idx1);
            }
            std::cout << "time: " << st.ns() << std::endl;
        }

        std::cout << "first: " << idx0 << 
        ",  second: " << idx1 << std::endl;

        return;
    }
    void Func001_For(const int *x, size_t xs, int target, size_t &res0, size_t &res1)
    {
        // first
        for(size_t i = 0; i < xs; ++i)
        {
            const auto tempTar = target - x[i];
            for (size_t j = 0; j < xs; ++j)
            {
                if (tempTar == x[j])
                {
                    res0 = i;
                    res1 = j;
                    return;
                }
            }
        }
        res0 = std::numeric_limits<size_t>::max();
    }

    void Func001_Hash(const int *x, size_t xs, int target, size_t &res0, size_t &res1)
    {
        // 这跟构造hashmap不要钱一样2333
        std::unordered_map<int, int> temp;

        for (size_t i = 0; i < xs; i++)
        {
            auto p = temp.find(target - x[i]);
            if(temp.end() != p)
            {
                res0 = i;
                res1 = p->second;
                return;
            }
            temp[x[i]] = i;
        }
        res0 = std::numeric_limits<size_t>::max();
    }
} // namespace LeetCode
