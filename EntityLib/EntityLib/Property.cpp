#include "include/EntityLib/Property.h"
#include "include/EntityLib/CopyProperty.h"

namespace Ent
{
    void Property::copyInto(Property& _dest, [[maybe_unused]] CopyMode _copyMode)
    {
        CopyProperty copier(_dest, OverrideValueSource::OverrideOrPrefab);
        visitRecursive(*this, copier);
    }

    Property Property::detach()
    {
        auto& jsonFile = getEntityLib()->createTempJsonFile();
        Property detached(getEntityLib()->newPropImpl(nullptr, getSchema(), "", &jsonFile));
        // copyInto(detached, CopyMode::CopyOverride);
        CopyProperty copier(detached, OverrideValueSource::OverrideOrPrefab, false);
        visitRecursive(*this, copier);
        return detached;
    }

    void Property::applyToPrefab()
    {
        // Have to remove removed items in arrays
        auto const prefabSource = getPrefab();
        auto const* const prefabPath = prefabSource.getFilePath();
        auto& newJson = getEntityLib()->createTempJsonFile();
        newJson = getEntityLib()->readJsonFile(prefabPath);
        auto const clonedPrefab = Property(getEntityLib(), getSchema(), prefabPath, &newJson);
        CopyProperty copier(clonedPrefab, OverrideValueSource::Override, false);
        visitRecursive(*this, copier);
        clonedPrefab.save();
        for (auto const* const field : getFieldNames())
        {
            getObjectField(field).unset();
        }
    }

    Property Property::mapRename(char const* _current, char const* _new)
    {
        auto newItem = insertMapItem(_new);
        CopyProperty copier(newItem, OverrideValueSource::OverrideOrPrefab, true);
        visitRecursive(*this, copier);
        auto currentItem = getMapItem(_current);
        visitRecursive(currentItem, copier);
        return newItem;
    }
    Property Property::mapRename(int64_t _current, int64_t _new) const
    {
        auto newItem = insertMapItem(_new);
        CopyProperty copier(newItem, OverrideValueSource::OverrideOrPrefab, true);
        auto currentItem = getMapItem(_current);
        visitRecursive(currentItem, copier);
        eraseMapItem(_current);
        return newItem;
    }
    Property Property::unionSetRename(char const* _current, char const* _new) const
    {
        auto newItem = insertUnionSetItem(_new);
        CopyProperty copier(newItem, OverrideValueSource::OverrideOrPrefab, true);
        auto currentItem = getUnionSetItem(_current);
        visitRecursive(currentItem, copier);
        eraseUnionSetItem(_current);
        return newItem;
    }
    Property Property::objectSetRename(char const* _current, char const* _new) const
    {
        auto const prefab = getPrefab();
        if (prefab.objectSetContains(_current))
        {
            throw CantRename(staticFormat(
                "Cant rename %s into %s, because it is already in prefab", _current, _new));
        }
        ENTLIB_ASSERT(getDataKind() == DataKind::objectSet);
        auto newItem = insertObjectSetItem(_new);
        CopyProperty copier(newItem, OverrideValueSource::OverrideOrPrefab, true);
        auto currentItem = getObjectSetItem(_current);
        visitRecursive(currentItem, copier);
        eraseObjectSetItem(_current);
        ENTLIB_DBG_ASSERT(objectSetContains(_new));
        return newItem;
    }
    Property Property::objectSetRename(int64_t _current, int64_t _new) const
    {
        auto newItem = insertObjectSetItem(_new);
        CopyProperty copier(newItem, OverrideValueSource::OverrideOrPrefab, true);
        auto currentItem = getObjectSetItem(_current);
        visitRecursive(currentItem, copier);
        eraseObjectSetItem(_current);
        return newItem;
    }

    std::vector<PrefabInfo> getPrefabHistory(Property const& _prop)
    {
        std::vector<PrefabInfo> result;
        // Follow the prefab links
        auto prefab = _prop.m_self.get();
        while (prefab != nullptr)
        {
            auto path = prefab->getRootNode()->getFilePath();
            auto nodeRef = prefab->makeAbsoluteNodeRef();
            result.emplace_back(std::move(path), std::move(nodeRef), prefab->sharedFromThis());
            prefab = prefab->getPrefab();
        }
        std::reverse(begin(result), end(result));
        return result;
    }
} // namespace Ent
