#include "include/EntityLib/EntityLib.h"

#include "Tools.h"
#include "SchemaLoader.h"
// #include "include/EntityLib/ComponentMerge.h"

#pragma warning(push, 0)
#pragma warning(disable : 4702)
#include <iostream>
#include <fstream>
#include <set>
// #include <sstream>
#include <utility>
#include <ciso646>
#include <thread>

#include "external/json.hpp"
// #include "ValidJson.h"
#include "include/EntityLib/Property.h"
#pragma warning(pop)

/// \cond PRIVATE

using namespace nlohmann;

namespace Ent
{
    char const* actorStatesSchemaName = "ActorStates";
    char const* colorSchemaName = "Color";
    char const* entitySchemaName = "Entity";
    char const* sceneSchemaName = "Scene";

    // canonical or weakly_canonical find the original physic drive but we want to keep X:
    // We also want to add '/' if the path is a letter (X:)
    // We also want path with forward slashes
    static std::filesystem::path very_weakly_canonical(std::filesystem::path const& _path)
    {
        std::filesystem::path c;
        for (auto const& iter : _path)
        {
            if (iter.string() == "..")
            {
                if (c.empty())
                {
                    c /= iter;
                }
                else
                {
                    c = c.parent_path();
                }
            }
            else if (iter.string() != ".")
            {
                c /= iter;
            }
        }
        if (c.string().back() == ':')
        {
            c = (c.string() + '/');
        }
        return c.make_preferred();
    }

    EntityLib::EntityLib(std::filesystem::path _rawdataPath, std::filesystem::path const& _schemaPath)
    {
        if ((_rawdataPath.string().back() != '/') || (_rawdataPath.string().back() != '\\'))
        {
            _rawdataPath = (_rawdataPath.string() + '/');
        }

        auto getAbsPath = [this](auto const& _path)
        {
            if (_path.is_absolute())
            {
                return very_weakly_canonical(_path);
            }
            else
            {
                return very_weakly_canonical(std::filesystem::current_path() / _path);
            }
        };

        rawdataPath = getAbsPath(_rawdataPath);
        m_schemaPath = getAbsPath(_schemaPath);
        auto toolsDir = getAbsolutePath(rootPath / "Tools");

        SchemaLoader loader(m_schemaPath);

        json schemaDocument = loadJsonFile("", m_schemaPath / "MergedComponents.json");

        loader.readSchema(&schema.schema, "MergedComponents.json", schemaDocument, schemaDocument);
        schema.schema.entityLib = this;

        static constexpr char WildComponentNameSuffix[] = "GD";
        auto const dependenciesPath = m_schemaPath / "Dependencies.json";
        if (exists(dependenciesPath))
        {
            json dependencies = loadJsonFile("", dependenciesPath);
            for (json const& comp : dependencies["Dependencies"])
            {
                auto name = comp["className"].get<std::string>() + WildComponentNameSuffix;
                std::vector<std::string> deps;
                for (json const& dep : comp["dependencies"])
                {
                    if (not dep["Optional"].get<bool>())
                    {
                        deps.push_back(dep["Name"].get<std::string>() + WildComponentNameSuffix);
                    }
                }
                componentDependencies.emplace(name, std::move(deps));

                std::vector<std::string> incompatibleComponents;
                for (json const& incompatibility : comp["incompatibilities"])
                {
                    incompatibleComponents.push_back(
                        incompatibility["Name"].get<std::string>() + WildComponentNameSuffix);
                }
                componentIncompatibilities.emplace(
                    std::move(name), std::move(incompatibleComponents));
            }
        }
    }

    EntityLib::~EntityLib() = default;

    static PropImplPtr getSubScene(PropImpl& _entity)
    {
        if (PropImplPtr const subScene =
                _entity.getObjectField("Components")->getUnionSetItem("SubScene"))
        {
            return subScene->getObjectField("Embedded");
        }
        return nullptr;
    }

    static PropImplPtr getSceneParentEntity(PropImpl* _scene)
    {
        PropImplPtr entity;
        ENTLIB_ASSERT(_scene != nullptr);
        ENTLIB_ASSERT(_scene->getDataKind() == DataKind::objectSet);
        // subSceneData can be null if rootScene was loaded with loadSceneAsNode
        if (auto const subSceneCpnt = _scene->getParent())
        {
            ENTLIB_ASSERT(subSceneCpnt != nullptr);
            ENTLIB_ASSERT(subSceneCpnt->getDataKind() == DataKind::object);
            auto const components = subSceneCpnt->getParent(); // Component union
            ENTLIB_ASSERT(components != nullptr);
            ENTLIB_ASSERT(components->getDataKind() == DataKind::unionSet);
            entity = components->getParent(); // Entity
            ENTLIB_ASSERT(entity != nullptr);
            ENTLIB_ASSERT(entity->getDataKind() == DataKind::object);
            ENTLIB_ASSERT_MSG(
                entity == nullptr || entity->getSchema()->name == entitySchemaName,
                "current has to be an Entity but is not!");
        }
        return entity;
    }

    static PropImplPtr resolveEntityRefRecursive(
        PropImplPtr _current, PropImplPtr _up, PropImplPtr _down, std::vector<std::string>& _path)
    {
        ENTLIB_ASSERT_MSG(
            _current == nullptr or _current->getSchema()->name == entitySchemaName,
            "_current has to be an Entity but is not!");

        auto const& head = _path.front();

        if (head == "..")
        {
            // go up in hierarchy
            if (_up == nullptr)
            {
                // broken ref
                return nullptr;
            }
            _current = getSceneParentEntity(_up.get());
            ENTLIB_ASSERT_MSG(
                _current == nullptr or _current->getSchema()->name == entitySchemaName,
                "_current has to be an Entity but is not!");
            _down = std::move(_up);
            _up = _current == nullptr ? nullptr : _current->getParent();
        }
        else if (head != ".")
        {
            // go down in child hierarchy named "head"
            if (_down == nullptr)
            {
                // broken ref
                return nullptr;
            }
            _current = _down->getObjectSetItem(head.c_str());
            _up = std::move(_down);
            _down = _current == nullptr ? nullptr : getSubScene(*_current);
        }
        _path.erase(_path.begin());
        if (_path.empty())
        {
            return _current;
        }
        return resolveEntityRefRecursive(
            std::move(_current), std::move(_up), std::move(_down), _path);
    }

    static PropImplPtr resolveEntityRefImpl(PropImplPtr _current, EntityRef const& _entityRef)
    {
        ENTLIB_ASSERT(_current != nullptr);
        if (_current->getSchema()->name != entitySchemaName)
        {
            throw ContextException("Can't resolveEntityRef because the Node in not an Entity");
        }
        if (_entityRef.entityPath.empty())
        {
            // empty ref
            return nullptr;
        }

        // split around '/'
        std::vector<std::string> parts = splitString(_entityRef.entityPath.c_str(), '/');

        PropImplPtr down = getSubScene(*_current);
        PropImplPtr up = _current->getParent();

        return resolveEntityRefRecursive(std::move(_current), std::move(up), std::move(down), parts);
    }

    Subschema const* EntityLib::getSchema(char const* _schemaName) const
    {
        if (auto const iter = schema.schema.allDefinitions.find(_schemaName);
            iter != schema.schema.allDefinitions.end())
        {
            return &iter->second;
        }
        return nullptr;
    }

    Subschema const* EntityLib::getEntitySchema() const
    {
        return getSchema(entitySchemaName);
    }

    Subschema const* EntityLib::getSceneSchema() const
    {
        return getSchema(sceneSchemaName);
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void EntityLib::setLogicErrorPolicy(LogicErrorPolicy _LogicErrorPolicy)
    {
        s_LogicErrorPolicy = _LogicErrorPolicy;
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    LogicErrorPolicy EntityLib::getLogicErrorPolicy() const
    {
        return s_LogicErrorPolicy;
    }

    static std::tuple<std::vector<std::string>, PropImplPtr, PropImplPtr>
    getAbsolutePathReversed(PropImplPtr _entity)
    {
        ENTLIB_ASSERT_MSG(
            _entity->getSchema()->name == entitySchemaName,
            "_entity has to be an Entity but is not!");
        PropImplPtr current = std::move(_entity);
        PropImplPtr rootEntity = nullptr;
        PropImplPtr rootScene = nullptr;
        std::vector<std::string> path;
        while (current != nullptr)
        {
            ENTLIB_ASSERT(current->getDataKind() == DataKind::object);
            path.emplace_back(current->getObjectField("Name")->getString());
            rootScene = current->getParent();
            rootEntity = std::move(current);
            current = nullptr;
            if (rootScene != nullptr)
            {
                current = getSceneParentEntity(rootScene.get());
            }
            ENTLIB_ASSERT_MSG(
                current == nullptr || current->getSchema()->name == entitySchemaName,
                "current has to be an Entity but is not!");
        }
        return {std::move(path), std::move(rootEntity), std::move(rootScene)};
    }

    std::optional<Property>
    EntityLib::resolveEntityRef(Property const& _node, EntityRef const& _entityRef) const
    {
        if (_node.getDataKind() == DataKind::objectSet) // This is a scene
        {
            if (_entityRef.entityPath.empty())
            {
                // empty ref
                return std::nullopt;
            }

            // split around '/'
            std::vector<std::string> parts = splitString(_entityRef.entityPath.c_str(), '/');

            PropImplPtr current = getSceneParentEntity(&_node.getPimpl());
            PropImplPtr down = _node.getPimpl().sharedFromThis();
            PropImplPtr up = current == nullptr ? nullptr : current->getParent();

            if (auto propptr = resolveEntityRefRecursive(
                    std::move(current), std::move(up), std::move(down), parts))
            {
                return Property(std::move(propptr));
            }
            return std::nullopt;
        }
        if (auto propPtr = resolveEntityRefImpl(_node.getPimpl().sharedFromThis(), _entityRef))
        {
            return Property(std::move(propPtr));
        }
        return std::nullopt;
    }

    EntityRef EntityLib::makeEntityRef(Property const& _from, Property const& _to) const
    {
        // get the two absolute path
        auto&& [thisPath, thisRootEntity, thisRootScene] =
            getAbsolutePathReversed(_from.getPimpl().sharedFromThis());
        auto&& [entityPath, entityRootEntity, entityRootScene] =
            getAbsolutePathReversed(_to.getPimpl().sharedFromThis());

        // entities should either share a common root scene
        // or a common root entity if they are in a .entity (i.e there is no root scene)
        if (thisRootScene != entityRootScene
            or thisRootEntity == nullptr and thisRootEntity != entityRootEntity)
        {
            // cannot reference unrelated entities
            return {};
        }

        std::string const relativePath = computeRelativePath(thisPath, std::move(entityPath), false);

        return {relativePath};
    }

    std::optional<Property> EntityLib::getParentEntity(Property const& _node) const
    {
        if (auto* const parent = _node.getPimpl().getParent().get())
        {
            if (auto ptr = getSceneParentEntity(parent))
            {
                return Property{std::move(ptr)};
            }
        }
        return std::nullopt;
    }

    Property EntityLib::loadProperty(char const* _schemaName, char const* _filepath)
    {
        return Property(this, getSchema(_schemaName), _filepath);
    }

    static std::string_view loadFunc(json const& _document, char const* _filepath)
    {
        if (auto const schemaName = _document.find("$schema"); schemaName != _document.end())
        {
            // If $schema found, use it
            return getRefTypeName(schemaName->get_ref<json::string_t const&>().c_str());
        }

        throw UnknownSchema("", _filepath);
    };

    Property EntityLib::loadProperty(char const* _filepath)
    {
        auto const& json = readJsonFile(_filepath);
        auto const schemaName = std::string(loadFunc(json.document, _filepath));

        return Property(this, getSchema(schemaName.c_str()), _filepath);
    }

    Property EntityLib::loadPropertyCopy(char const* _schemaName, char const* _filepath)
    {
        auto& copy = createTempJsonFile(_schemaName);
        auto& storage = readJsonFile(_filepath);
        copy.document = storage.document;
        return Property(this, getSchema(_schemaName), _filepath, copy);
    }

    Property EntityLib::loadPropertyCopy(char const* _filepath)
    {
        auto& copy = createTempJsonFile(nullptr);
        auto& storage = readJsonFile(_filepath);
        copy.document = storage.document;
        auto const schemaName = std::string(loadFunc(copy.document, _filepath));
        return Property(this, getSchema(schemaName.c_str()), _filepath, copy);
    }

    Property EntityLib::newProperty(Subschema const* _schema)
    {
        auto& storage = createTempJsonFile(_schema->name.c_str());
        return Property(this, _schema, "", storage);
    }

    VersionedJson& EntityLib::readJsonFile(char const* _filepath) const
    {
        auto const absPath = getAbsolutePath(_filepath);
        std::filesystem::path const absPathLower = strToLower(absPath.generic_string());
        if (auto const iter = m_jsonDatabase.find(absPathLower); iter != m_jsonDatabase.end())
        {
            return *iter->second;
        }
        if (m_newDepFileCallback)
        {
            m_newDepFileCallback(_filepath);
        }
        auto file = std::make_unique<VersionedJson>();
        file->document = loadJsonFile(rawdataPath, absPath);
        auto error = std::error_code{};
        auto const timestamp = last_write_time(absPath, error);
        if (error)
        {
            throw FileSystemError("Trying to get last write time", rawdataPath, absPath, error);
        }
        else
        {
            file->metadata.time = timestamp;
        }
        return *m_jsonDatabase.emplace(absPathLower, std::move(file)).first->second;
    }

    VersionedJson& EntityLib::createTempJsonFile(char const* _schemaName) const
    {
        auto& doc = *m_tempJsonFiles.emplace_back(std::make_unique<VersionedJson>());
        if (_schemaName != nullptr and strlen(_schemaName) != 0)
        {
            doc.document["$schema"] = format(schemaFormat, _schemaName);
        }
        return doc;
    }

    template <typename Lambda>
    static void try3Times(Lambda&& lambda)
    {
        for (size_t i = 0;; ++i)
        {
            try
            {
                lambda();
                return;
            }
            catch (...)
            {
                if (i == 2)
                {
                    throw;
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    }

    void EntityLib::saveJsonFile(json const* doc, char const* _filepath, char const* _schema) const
    {
        auto const absPath = getAbsolutePath(_filepath);
        auto const tempFilename = std::filesystem::path(absPath.string() + ".tmp");
        create_directories(tempFilename.parent_path());
        {
            std::ofstream ofs(tempFilename);
            if (not ofs.is_open())
            {
                throw ContextException("Can't open %s for write", tempFilename.string().c_str());
            }
            // We don't want to add "$schema" in doc because sometime it is not the root node
            json copy = *doc;
            if (_schema != nullptr)
            {
                copy["$schema"] = format(schemaFormat, _schema);
            }
            ofs << copy.dump(4);
        }
        try3Times([&] { rename(tempFilename, absPath); });
        std::filesystem::path const absPathLower = strToLower(absPath.generic_string());
        if (m_jsonDatabase.count(absPathLower) == 0)
        {
            m_jsonDatabase[absPathLower] = std::make_unique<VersionedJson>();
        }
        if (&(m_jsonDatabase[absPathLower]->document) != doc)
        {
            m_jsonDatabase[absPathLower]->document = *doc;
            ++m_jsonDatabase[absPathLower]->metadata.version;
            auto error = std::error_code{};
            auto const timestamp = last_write_time(absPath, error);
            if (error)
            {
                throw FileSystemError("Trying to get last write time", rawdataPath, absPath, error);
            }
            else
            {
                m_jsonDatabase[absPathLower]->metadata.time = timestamp;
            }
        }
    }

    void EntityLib::saveJsonFileDatabase(char const* _customRootpath) const
    {
        // to handle situations where the absolute file paths are too long,
        // we temporarily change the current directory to the root before saving entities using relative paths
        std::filesystem::path const previousCurPath = std::filesystem::current_path();
        if (_customRootpath != nullptr)
        {
            auto const absPath = getAbsolutePath(_customRootpath);
            std::filesystem::current_path(absPath);
        }
        else
        {
            std::filesystem::current_path(rawdataPath);
        }

        for (auto const& [path, versionedJson] : m_jsonDatabase)
        {
            std::filesystem::path relPath = relative(path, rawdataPath);
            auto const tempFilename = std::filesystem::path(relPath.string() + ".tmp");
            create_directories(tempFilename.parent_path());
            {
                std::ofstream ofs(tempFilename);
                if (not ofs.is_open())
                {
                    throw ContextException("Can't open %s for write", tempFilename.string().c_str());
                }
                json copy = versionedJson->document;
                ofs << copy.dump(4);
            }
            try3Times([&] { rename(tempFilename, relPath); });
        }

        std::filesystem::current_path(previousCurPath);
    }

    std::vector<std::pair<std::filesystem::path, JSonFileState>> EntityLib::collectOutdatedJsonFiles() const
    {
        std::vector<std::pair<std::filesystem::path, JSonFileState>> collectedPaths;

        for (auto const& [path, versionedJson] : m_jsonDatabase)
        {
            auto error = std::error_code{};
            auto const timestamp = last_write_time(path, error);
            if (error)
            {
                collectedPaths.push_back(std::pair(path, JSonFileState::Deleted));
            }
            else if (timestamp > versionedJson->metadata.time)
            {
                collectedPaths.push_back(std::pair(path, JSonFileState::Modified));
            }
        }

        return collectedPaths;
    }

    void EntityLib::reloadJsonFiles(std::vector<std::filesystem::path> const& _filePaths) const
    {
        for (auto const& absPath : _filePaths)
        {
            if (auto const iter = m_jsonDatabase.find(absPath); iter != m_jsonDatabase.end())
            {
                auto const& [path, versionedJson] = *iter;
                versionedJson->document = loadJsonFile(rawdataPath, path);
                auto error = std::error_code{};
                auto const timestamp = last_write_time(absPath, error);
                if (error)
                {
                    throw FileSystemError(
                        "Trying to get last write time", rawdataPath, absPath, error);
                }
                else
                {
                    versionedJson->metadata.time = timestamp;
                }
            }
            else
            {
                throw FileSystemError(
                    "Trying to reload file that was never loaded in the first place",
                    rawdataPath,
                    absPath);
            }
        }
    }

    /// Exception thrown when a method is called on legacy data (or vice versa)
    struct UnsupportedFormat : ContextException
    {
        UnsupportedFormat() = default;
    };

    PropImplPtr EntityLib::newPropImpl()
    {
        PropImpl* property{};
        auto* mem = propertyPool.alloc();
        try
        {
            property = new (mem) PropImpl(this);
        }
        catch (...)
        {
            propertyPool.free(mem);
            throw;
        }
        return property->sharedFromThis();
    }

    PropImplPtr EntityLib::newPropImpl(
        PropImplPtr _parent,
        Subschema const* _schema,
        char const* _filename,
        json* _doc,
        JsonMetaData* _metadata)
    {
        PropImpl* property{};
        auto* mem = propertyPool.alloc();
        try
        {
            property =
                new (mem) PropImpl(this, std::move(_parent), _schema, _filename, _doc, _metadata);
        }
        catch (...)
        {
            propertyPool.free(mem);
            throw;
        }
        return property->sharedFromThis();
    }

    std::filesystem::path EntityLib::getAbsolutePath(std::filesystem::path const& _path) const
    {
        if (_path.is_absolute())
        {
            return very_weakly_canonical(_path);
        }
        std::filesystem::path absPath = rawdataPath;
        absPath /= _path;
        return very_weakly_canonical(absPath);
    }

    std::filesystem::path EntityLib::getRelativePath(std::filesystem::path const& _path) const
    {
        if (_path.is_absolute())
        {
            // Check if _path is inside rawdataPath
            std::filesystem::path parent = _path;
            std::filesystem::path relPath;
            while (!equivalent(parent, rawdataPath))
            {
                if (parent.has_parent_path() and !equivalent(parent.parent_path(), parent))
                {
                    if (relPath.empty())
                    {
                        relPath = parent.filename();
                    }
                    else
                    {
                        relPath = parent.filename() / relPath;
                    }
                    parent = parent.parent_path();
                }
                else
                {
                    throw ContextException(
                        R"(_path %s in not inside rawdata "%s")",
                        formatPath(rawdataPath, _path),
                        rawdataPath.generic_string().c_str());
                }
            }

            return relPath;
        }
        return _path;
    }

    auto EntityLib::HashPath::operator()(std::filesystem::path const& p) const
    {
        return hash_value(p);
    }

    std::unordered_map<std::filesystem::path, std::unique_ptr<VersionedJson>, EntityLib::HashPath> const&
    EntityLib::getJsonDatabase() const
    {
        return m_jsonDatabase;
    }

    void EntityLib::setFallBackEntityPath(char const* _filePath)
    {
        m_fallbackEntity = _filePath;
    }

    char const* EntityLib::getFallBackEntityPath() const
    {
        return m_fallbackEntity.c_str();
    }

    void EntityLib::setNewDepFileCallBack(NewDepFileCallback _callback)
    {
        m_newDepFileCallback = std::move(_callback);
    }

    size_t EntityLib::getGlobalDocumentsVersion() const
    {
        return m_globalDocumentsVersion;
    }

    void EntityLib::incrementGlobalDocumentsVersion()
    {
        ++m_globalDocumentsVersion;
    }

    bool EntityLib::getRebuildPropertyEnabled() const
    {
        return m_rebuildPropertyEnabled;
    }

    void EntityLib::setRebuildPropertyEnabled(bool _rebuildPropertyEnabled)
    {
        m_rebuildPropertyEnabled = _rebuildPropertyEnabled;
    }

    std::filesystem::path EntityLib::getSchemaPath() const
    {
        return m_schemaPath;
    }

    /// \endcond
} // namespace Ent
