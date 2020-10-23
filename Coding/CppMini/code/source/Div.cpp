#include "Div.hpp"
#include "timeHelper.hpp"

#include <vector>
#include <array>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace Div
{
    constexpr size_t g_CupCount = 8; 
    constexpr std::array<unsigned, g_CupCount> g_CupInner{ /*31, 29,*/ 23, 19, 17, 13, 11, 7, 5, 2 };

    using State = std::array<unsigned, g_CupCount>;

    struct StateHashNonUni
    {
        static std::array<unsigned, g_CupCount - 1> offset;

        static void BuildHash(const State& maxState)
        {
            for (size_t i = 0; i < g_CupCount - 1; i++)
            {
                unsigned i_off;
                auto off_d = log2(maxState[i]);
                auto off_u = (unsigned)off_d;
                if ((off_d - off_u) > 0.001)
                {
                    i_off = off_u + 1;
                }
                else
                {
                    i_off = off_u;
                }
                offset[i] = i_off;
                std::cout << i_off << '\t';
            }
        }
    
        size_t operator()(const State& state) const
        {
            size_t res = 0;
            for (size_t i = 0; i < g_CupCount - 1; i++)
            {
                res += state[i];
                res = res << offset[i];
            }
            res += state[g_CupCount - 1];
            return res;
        }
    };
    std::array<unsigned, g_CupCount - 1> StateHashNonUni::offset;

    struct StateHashUni
    {
        struct helper
        {
            uint16_t _1;
            uint16_t _2;
            uint16_t _3;
            uint16_t _4;
        };

        size_t operator()(const State& state) const
        {
            helper res;
            res._1 = state[0];
            res._2 = state[1];
            res._3 = state[2];
            res._4 = state[3];

            auto *t = reinterpret_cast<size_t *>(&res);
            return *t;
        }
    };

    struct StateHashFix
    {       
        size_t operator()(const State &state) const
        {
            size_t res = 0;
            res += state[0];
            res = res << 5;

            res += state[1];
            res = res << 5;

            res += state[2];
            res = res << 3;
            
            res += state[3];

            return res;
        }
    };
    

    struct StateHash
    {
        inline size_t operator()(const State& state) const
        {
            return hasher(state);
        }
        StateHashNonUni hasher;
    };
    // 保存分层状态数据
    std::vector<std::unordered_set<State, StateHash>> g_layers;

    // 保存依赖关系 Todo
    struct Node
    {
        std::vector<State> children;
        State state;

        void FitNode()
        {
            children.shrink_to_fit();
        }

    };

    bool operator==(const Node& lhs, const Node &rhs)
    {
        return lhs.state == rhs.state;
    }

    struct NodeHash
    {
        size_t operator()(const Node& node) const
        {
            return m_Hasher(node.state);
        }

        StateHash m_Hasher;
    };

    std::unordered_set<Node, NodeHash> g_nodes;
    
    struct GNode
    {
        unsigned layer;
        std::vector<State *> parents;
        std::vector<State *> children;
    };


    bool IsExist(const State& state)
    {
        auto length = g_layers.size();
        for (size_t i = 0; i < length; i++)
        {   
            auto &layer = g_layers[i];
            if (layer.end() != layer.find(state))
            {
                return true;
            }
        }
        return false;
    }

    inline State WorkOnce(const State& state, const size_t f, const size_t t)
    {
        State res = state;
        auto inner = g_CupInner[t] - state[t];
        if (inner > state[f])
        {
            res[f] = 0; 
            res[t] += state[f];
        }
        else
        {
            res[f] -= inner;
            res[t] += inner;
        }
        
        return res;
    }

    void FindNextState(const State &state, std::vector<State>& nextLayer)
    {
        for (size_t i = 0; i < g_CupCount; i++)
        {
            for (size_t j = 0; j < i; j++)
            {
                auto new_state = WorkOnce(state, i, j);
                if (!IsExist(new_state))
                {
                    nextLayer.push_back(new_state);
                    
                }
            }
            
            for (size_t j = i + 1; j < g_CupCount; j++)
            {
                auto new_state = WorkOnce(state, i, j);
                if (!IsExist(new_state))
                {
                    nextLayer.push_back(new_state);
                }
            }
        }
    }

    void FindNextState(const State &state, std::unordered_set<State, StateHash>& nextLayer)
    {
        Node node;
        node.state = state;
        for (size_t i = 0; i < g_CupCount; i++)
        {
            for (size_t j = 0; j < i; j++)
            {
                auto new_state = WorkOnce(state, i, j);
                if (!IsExist(new_state))
                {
                    nextLayer.insert(new_state);
                    node.children.push_back(new_state);
                }
            }
            
            for (size_t j = i + 1; j < g_CupCount; j++)
            {
                auto new_state = WorkOnce(state, i, j);
                if (!IsExist(new_state))
                {
                    nextLayer.insert(new_state);
                    node.children.push_back(new_state);
                }
            }
        }
        //g_nodes.insert(node);
    }

    void FindNextLayerState(unsigned layerIdx)
    {
        if (layerIdx >= g_layers.size())
        {
            return;
        }

        if ((g_layers.size()) - 1 == layerIdx)
        {
            g_layers.emplace_back();
        }
        g_layers[layerIdx + 1].clear();

        for(const auto &state : g_layers[layerIdx])
        {
            FindNextState(state, g_layers[layerIdx + 1]);
        }
    }

    bool IsEnd()
    {
        static size_t counter = 0;
        if (g_layers[g_layers.size() - 1].size() > 0)
        {
            counter++;
            return false;
        }
        return true;
    }

    inline void OutputState(std::ostream &os, const State &state)
    {
        for (size_t i = 0; i < g_CupCount; i++)
        {
            os << state[i] << '\t';
        }
    }

    void OutputLayers(std::ostream &os)
    {
        int layerCounter = 0;
        for(const auto &layer : g_layers)
        {
            os << "Layer " << std::to_string(layerCounter++) << '\n';
            for(const auto &state : layer) 
            {
                for (size_t i = 0; i < g_CupCount; i++)
                {
                    os << state[i] << '\t';
                }
                os << '\n';
            }
            os << '\n' << std::endl;
        }
    }

    void OutputNodes(std::ostream &os)
    {
        os << std::to_string(g_nodes.size()) <<  " Nodes\n\n";

        for(const auto &node : g_nodes)
        {
            if (0 == node.children.size())
            {
                continue;
            }
            
            os << "Node : ";
            OutputState(os, node.state);
            os << '\n';
            for(const auto &cs : node.children)
            {
                os << '\t';
                OutputState(os, cs);
                os << '\n';
            }
            os << '\n';
        }
    }
    
    void Main()
    {
        StateHashNonUni::BuildHash(g_CupInner);
        g_layers.emplace_back();
        State start_state;
        g_layers[0];
        std::cout << "Input the start state." << std::endl;
        for (size_t i = 0; i < g_CupCount; i++)
        {
            std::cout << "Input " << std::to_string(i) << " cup, max inner is " 
            << std::to_string(g_CupInner[i]) << "\n";
            std::cin >> start_state[i];
        }

        g_layers[0].insert(start_state);
        
        system("clear");
        unsigned long dt = 0;
        {
            Hy::ScopeTimer st;
            int layerCount = 0;
            while (!IsEnd())
            {
                std::cout << layerCount <<'\n';
                FindNextLayerState(layerCount);
                ++layerCount;

            }
            dt = st.ms();
        }
        std::cout << "\nTime(ms) : " << dt << std::endl;
        g_layers.pop_back();

        std::ofstream layerFile(R"(../bin/layer.txt)");
        OutputLayers(layerFile);

        std::ofstream file(R"(../bin/node.txt)");
        OutputNodes(file);


    }
} // namespace Div
