#include "include/EntityLib/Property.h"
#include "include/EntityLib/CopyProperty.h"

namespace Ent
{
    Property::Property(EntityLib* _entityLib, Subschema const* _schema, char const* _filename)
        : m_self(_entityLib->newPropImpl(nullptr, _schema, _filename, nullptr, nullptr))
    {
    }
    Property::Property(
        EntityLib* _entityLib,
        Subschema const* _schema,
        char const* _filename,
        nlohmann::json* _doc,
        JsonMetaData* _metaData)
        : m_self(_entityLib->newPropImpl(nullptr, _schema, _filename, _doc, _metaData))
    {
    }

    Property::Property(
        EntityLib* _entityLib, Subschema const* _schema, char const* _filename, VersionedJson& _doc)
        : Property(_entityLib, _schema, _filename, &_doc.document, &_doc.metadata)
    {
    }

    void Property::copyInto(
        Property const& _dest,
        [[maybe_unused]] CopyMode _copyMode,
        [[maybe_unused]] OverrideValueSource _overrideValueSource) const
    {
        CopyProperty copier(_dest, _overrideValueSource, _copyMode);
        visitRecursive(*this, copier);
    }

    Property Property::detach()
    {
        auto& jsonFile = getEntityLib()->createTempJsonFile(getSchema()->name.c_str());
        Property detached(getEntityLib()->newPropImpl(
            nullptr, getSchema(), "", &jsonFile.document, &jsonFile.metadata));
        CopyProperty copier(
            detached, OverrideValueSource::OverrideOrPrefab, CopyMode::CopyOverride, false);
        visitRecursive(*this, copier);
        return detached;
    }

    Property Property::clone()
    {
        if (auto prefab = getPimpl().getPrefab())
        {
            // If "this" has a prefab, make an instance of the prefab, then copy only overrides
            auto copy = Property(prefab->makeInstanceOf());
            ENTLIB_ASSERT(prefab == &copy.getPrefab()->getPimpl());
            CopyProperty copier(copy, OverrideValueSource::Override, CopyMode::CopyOverride, false);
            visitRecursive(*this, copier);
            ENTLIB_ASSERT(prefab == &copy.getPrefab()->getPimpl());
            return copy;
        }
        // If "this" has no prefab, create an empty document, then copy only overrides
        auto& jsonFile = getEntityLib()->createTempJsonFile(getSchema()->name.c_str());
        Property copy(getEntityLib()->newPropImpl(
            nullptr, getSchema(), "", &jsonFile.document, &jsonFile.metadata));
        CopyProperty copier(copy, OverrideValueSource::Override, CopyMode::CopyOverride);
        visitRecursive(*this, copier);
        return copy;
    }

    void Property::applyToPrefab()
    {
        // Have to remove removed items in arrays
        auto const prefabSource = getPrefab();
        if (not prefabSource.has_value())
        {
            throw ContextException("Can't applyToPrefab since Property has no prefab");
        }
        auto const* const prefabPath = prefabSource->getFilePath();
        auto& newJson = getEntityLib()->createTempJsonFile(getSchema()->name.c_str());
        newJson.document = getEntityLib()->readJsonFile(prefabPath).document;
        auto const clonedPrefab = Property(getEntityLib(), getSchema(), prefabPath, newJson);
        CopyProperty copier(
            clonedPrefab, OverrideValueSource::Override, CopyMode::CopyOverride, false);
        visitRecursive(*this, copier);
        clonedPrefab.save();
        for (auto const* const field : getFieldNames())
        {
            getObjectField(field).unset();
        }
    }

    Property Property::mapRename(char const* _current, char const* _new)
    try
    {
        auto newItem = insertMapItem(_new);
        CopyProperty copier(
            newItem, OverrideValueSource::OverrideOrPrefab, CopyMode::CopyOverride, true);
        visitRecursive(*this, copier);
        auto currentItem = getMapItem(_current);
        visitRecursive(*currentItem, copier);
        return newItem;
    }
    catch (ContextException& ex)
    {
        ex.addContextMessage(getDebugString());
        throw;
    }
    Property Property::mapRename(int64_t _current, int64_t _new) const
    try
    {
        auto newItem = insertMapItem(_new);
        CopyProperty copier(
            newItem, OverrideValueSource::OverrideOrPrefab, CopyMode::CopyOverride, true);
        auto currentItem = getMapItem(_current);
        visitRecursive(*currentItem, copier);
        eraseMapItem(_current);
        return newItem;
    }
    catch (ContextException& ex)
    {
        ex.addContextMessage(getDebugString());
        throw;
    }
    Property Property::unionSetRename(char const* _current, char const* _new) const
    {
        auto newItem = insertUnionSetItem(_new);
        CopyProperty copier(
            newItem, OverrideValueSource::OverrideOrPrefab, CopyMode::CopyOverride, true);
        auto currentItem = *getUnionSetItem(_current);
        visitRecursive(currentItem, copier);
        eraseUnionSetItem(_current);
        return newItem;
    }

    std::map<char const*, Property, CmpStr> Property::getMapStringItems() const
    try
    {
        std::map<char const*, Property, CmpStr> result;
        for (char const* key : getPimpl().getMapKeysString())
        {
            result.emplace(key, getPimpl().getMapItem(key));
        }
        return result;
    }
    catch (ContextException& ex)
    {
        ex.addContextMessage(getDebugString());
        throw;
    }

    std::map<int64_t, Property> Property::getMapIntItems() const
    try
    {
        std::map<int64_t, Property> result;
        for (int64_t key : getPimpl().getMapKeysInt())
        {
            result.emplace(key, getPimpl().getMapItem(key));
        }
        return result;
    }
    catch (ContextException& ex)
    {
        ex.addContextMessage(getDebugString());
        throw;
    }
    std::vector<Property> Property::getObjectSetItems() const
    {
        std::vector<Property> result;
        auto const keyType = getPimpl().getObjectSetKeyType();
        if (keyType == DataType::string or keyType == DataType::entityRef)
        {
            for (char const* key : getPimpl().getObjectSetKeysString())
            {
                result.emplace_back(getPimpl().getObjectSetItem(key));
            }
        }
        else if (keyType == DataType::integer)
        {
            for (auto const key : getPimpl().getObjectSetKeysInt())
            {
                result.emplace_back(getPimpl().getObjectSetItem(key));
            }
        }
        else
        {
            ENTLIB_LOGIC_ERROR("Unexpected ObjectSetKeyType in getObjectSetItems()");
        }
        return result;
    }

    std::map<char const*, Property, CmpStr> Property::getUnionSetItems() const
    {
        std::map<char const*, Property, CmpStr> result;
        for (auto&& [key, schema] : getPimpl().getUnionSetKeysString())
        {
            result.emplace(key, getPimpl().getUnionSetItem(key));
        }
        return result;
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

    char const* Property::getDebugString() const
    {
        auto getIsSetLevel = [](Property const& _prop)
        {
            // Get the distance to the first parent which is set
            auto setLevel = 0;
            std::optional parent = _prop;
            while (parent.has_value() and not parent->isSet())
            {
                parent = parent->getParent();
                ++setLevel;
            }
            return setLevel;
        };

        // Find the prefab which has json data closest to target property
        auto minSetLevel = ~size_t();
        PrefabInfo const* bestPrefabInfo = nullptr;
        auto histories = getPrefabHistory(*this);
        std::reverse(begin(histories), end(histories));
        for (auto const& histo : histories)
        {
            auto const setLevel = getIsSetLevel(histo.prop);
            if (setLevel < minSetLevel)
            {
                minSetLevel = setLevel;
                bestPrefabInfo = &histo;
            }
        }
        if (bestPrefabInfo != nullptr)
        {
            return staticFormat(
                R"("%s" - "%s")", bestPrefabInfo->prefabPath.c_str(), bestPrefabInfo->nodeRef.c_str());
        }
        return staticFormat(
            R"("%s" - "%s")", histories[0].prefabPath.c_str(), histories[0].nodeRef.c_str());
    }
} // namespace Ent
