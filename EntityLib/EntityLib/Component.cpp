#include "Component.h"

#include "MemoryProfiler.h"
#include "external/json.hpp"

using namespace nlohmann;

namespace Ent
{
    Component::Component(bool _hasPrefab, std::string _type, Node _root, size_t _version, size_t _index)
        : type(std::move(_type))
        , root(std::move(_root))
        , version(_version)
        , index(_index)
        , hasPrefab(_hasPrefab)
    {
        root.setAddedInInsance(!_hasPrefab);
    }

    Component Component::makeInstanceOf() const
    {
        return Component{true, type, root.makeInstanceOf(), version, index};
    }

    bool Component::hasOverride() const
    {
        return root.hasOverride();
    }

    bool Component::hasDefaultValue() const
    {
        return root.hasDefaultValue();
    }

    bool Component::isUsedInRuntime() const
    {
        return root.getSchema() != nullptr && root.getSchema()->IsUsedInRuntime();
    }

    bool Component::isUsedInEditor() const
    {
        return root.getSchema() != nullptr && root.getSchema()->IsEditorOnly();
    }

    void Component::applyAllValues(Component& _dest, CopyMode _copyMode) const
    {
        ENTLIB_ASSERT(type == _dest.type);
        root.applyAllValues(_dest.root, _copyMode);
    }

    void Component::computeMemory(MemoryProfiler& prof) const
    {
        prof.currentComp.push_back(type.c_str());
        prof.addMem("Component::type", type.size());
        root.computeMemory(prof);
        prof.currentComp.pop_back();
    }

} // namespace Ent
