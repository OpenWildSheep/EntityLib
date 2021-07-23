#include "Component.h"

#include "MemoryProfiler.h"

using namespace nlohmann;

namespace Ent
{

    void Component::computeMemory(MemoryProfiler& prof) const
    {
        prof.currentComp.push_back(type.c_str());
        prof.addMem("Component::type", type.size());
        root.computeMemory(prof);
        prof.currentComp.pop_back();
    }

} // namespace Ent
