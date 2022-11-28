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
        Property& _dest,
        [[maybe_unused]] CopyMode _copyMode,
        [[maybe_unused]] OverrideValueSource _overrideValueSource)
    {
        CopyProperty copier(_dest, _overrideValueSource, _copyMode);
        visitRecursive(*this, copier);
    }

    Property Property::detach()
    {
        auto& jsonFile = getEntityLib()->createTempJsonFile();
        Property detached(getEntityLib()->newPropImpl(
            nullptr, getSchema(), "", &jsonFile.document, &jsonFile.metadata));
        CopyProperty copier(
            detached, OverrideValueSource::OverrideOrPrefab, CopyMode::CopyOverride, false);
        visitRecursive(*this, copier);
        return detached;
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
        auto& newJson = getEntityLib()->createTempJsonFile();
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
    {
        auto newItem = insertMapItem(_new);
        CopyProperty copier(
            newItem, OverrideValueSource::OverrideOrPrefab, CopyMode::CopyOverride, true);
        visitRecursive(*this, copier);
        auto currentItem = getMapItem(_current);
        visitRecursive(*currentItem, copier);
        return newItem;
    }
    Property Property::mapRename(int64_t _current, int64_t _new) const
    {
        auto newItem = insertMapItem(_new);
        CopyProperty copier(
            newItem, OverrideValueSource::OverrideOrPrefab, CopyMode::CopyOverride, true);
        auto currentItem = getMapItem(_current);
        visitRecursive(*currentItem, copier);
        eraseMapItem(_current);
        return newItem;
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
    Property Property::objectSetRename(char const* _current, char const* _new) const
    {
        auto const prefab = getPrefab();
        if (not prefab.has_value())
        {
            throw ContextException("Can't applyToPrefab since Property has no prefab");
        }
        if (prefab->objectSetContains(_current))
        {
            throw CantRename(staticFormat(
                "Cant rename %s into %s, because it is already in prefab", _current, _new));
        }
        ENTLIB_ASSERT(getDataKind() == DataKind::objectSet);
        auto newItem = insertObjectSetItem(_new);
        CopyProperty copier(
            newItem, OverrideValueSource::OverrideOrPrefab, CopyMode::CopyOverride, true);
        auto currentItem = getObjectSetItem(_current);
        visitRecursive(*currentItem, copier);
        eraseObjectSetItem(_current);
        ENTLIB_DBG_ASSERT(objectSetContains(_new));
        return newItem;
    }
    Property Property::objectSetRename(int64_t _current, int64_t _new) const
    {
        auto newItem = insertObjectSetItem(_new);
        CopyProperty copier(
            newItem, OverrideValueSource::OverrideOrPrefab, CopyMode::CopyOverride, true);
        auto currentItem = getObjectSetItem(_current);
        visitRecursive(*currentItem, copier);
        eraseObjectSetItem(_current);
        return newItem;
    }

    std::map<char const*, Property> Property::getMapStringItems() const
    {
        std::map<char const*, Property> result;
        for (char const* key : getPimpl().getMapKeysString())
        {
            result.emplace(key, getPimpl().getMapItem(key));
        }
        return result;
    }

    std::map<int64_t, Property> Property::getMapIntItems() const
    {
        std::map<int64_t, Property> result;
        for (int64_t key : getPimpl().getMapKeysInt())
        {
            result.emplace(key, getPimpl().getMapItem(key));
        }
        return result;
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

    std::map<char const*, Property> Property::getUnionSetItems() const
    {
        std::map<char const*, Property> result;
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
} // namespace Ent
