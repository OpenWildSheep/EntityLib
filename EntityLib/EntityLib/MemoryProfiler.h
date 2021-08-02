#pragma once

#include <map>
#include <vector>

namespace Ent
{
    struct CompStr
    {
        bool operator()(char const* a, char const* b) const
        {
            return strcmp(a, b) < 0;
        }
    };

    struct MemoryProfiler
    {
        std::map<char const*, size_t, CompStr> mem;
        size_t total = 0;
        size_t nodeCount = 0;
        std::map<char const*, size_t, CompStr> nodeByComp;
        std::vector<char const*> currentComp;

        void addMem(char const* name, size_t value)
        {
            mem[name] += value;
            total += value;
        }

        void addNodes(size_t count)
        {
            nodeCount += count;
            nodeByComp[currentComp.back()] += count;
        }
    };

} // namespace Ent
