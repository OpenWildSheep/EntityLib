#pragma once

#include <functional>

#pragma warning(push)
#pragma warning(disable : 4464)
#include "../MemoryProfiler.h"
#include "../PropImpl.h"
#pragma warning(pop)

namespace Ent
{
    class EntityLib;
    struct Property;

    // ********************************** Static data *********************************************

    extern char const* entitySchemaName;
    extern char const* sceneSchemaName;

    /// Definition of all components
    struct ComponentsSchema
    {
        ComponentsSchema() = default;
        ComponentsSchema(ComponentsSchema const&) = delete;
        ComponentsSchema& operator=(ComponentsSchema const&) = delete;
        std::map<std::string, Subschema*> components; ///< Schema of all possible Components
        std::map<std::string, Subschema*> actorstates; ///< Schema of all possible Actorstates
        Schema schema; ///< Schemas of everything (object, enum...)

        /// @cond PRIVATE
        DeleteCheck deleteCheck; // Just for debug
        /// @endcond
    };

    struct JsonMetaData
    {
        JsonMetaData() = default;
        JsonMetaData(JsonMetaData const&) = delete;
        JsonMetaData& operator=(JsonMetaData const&) = delete;

        size_t version = 0;
        std::filesystem::file_time_type time;
    };

    struct VersionedJson
    {
        JsonMetaData metadata;
        nlohmann::json document = nlohmann::json::object();
    };

    enum class JSonFileState
    {
        Modified,
        Deleted,
        Count
    };

    /// Entry point of the EntityLib. Used to load/save Scene/Entity and to parse the Schema
    class ENTLIB_DLLEXPORT EntityLib
    {
    public:
        mutable Pool<PropImpl> propertyPool;
        /// @todo Make public attribute private?
        std::filesystem::path rootPath; ///< Path to the perforce root (X:/)
        std::filesystem::path rawdataPath; ///< Path to the RawData dir in the perforce root (X:/RawData)
        std::filesystem::path toolsDir; ///< Path to the Tools dir in in the perforce root (X:/Tools)
        ComponentsSchema schema; ///< Schema of all components
        bool validationEnabled = false; ///< validate all objects at load/save

        /// Component needed for each type of components
        std::map<std::string, std::vector<std::string>> componentDependencies;

        /// Incompatible components for each type of components
        std::map<std::string, std::vector<std::string>> componentIncompatibilities;

        /// Load the EntityLib, given the path to the Tools directory
        explicit EntityLib(std::filesystem::path const& _rootPath, bool _doMergeComponents = false);
        ~EntityLib();
        /// @cond PRIVATE
        EntityLib(EntityLib const&) = delete;
        EntityLib& operator=(EntityLib const&) = delete;
        DeleteCheck deleteCheck;

        PropImplPtr newPropImpl();
        PropImplPtr newPropImpl(
            PropImplPtr _parent,
            Subschema const* _schema,
            char const* _filename,
            nlohmann::json* _doc,
            JsonMetaData* _metadata);
        /// @endcond

        struct HashPath
        {
            auto operator()(std::filesystem::path const& p) const;
        };
        std::unordered_map<std::filesystem::path, std::unique_ptr<VersionedJson>, HashPath> const&
        getJsonDatabase() const;

        std::filesystem::path getAbsolutePath(std::filesystem::path const& _path) const;
        /// @param _path : A file path absolute or relative but inside the rawdata path
        std::filesystem::path getRelativePath(std::filesystem::path const& _path) const;

        Subschema const* getSchema(char const* _schemaName) const;
        Subschema const* getEntitySchema() const;
        Subschema const* getSceneSchema() const;

        void setLogicErrorPolicy(LogicErrorPolicy _LogicErrorPolicy);
        LogicErrorPolicy getLogicErrorPolicy() const;

        /// @brief Resolve an EntityRef relative to this Node/Entity.
        /// Returns nullptr in case of failure.
        std::optional<Property> resolveEntityRef(Property const& _node, EntityRef const& _entityRef) const;
        /// @brief Compute the EntityRef going from the Entity _from, to the Entity _to
        /// @pre _from and _to are Entity nodes
        EntityRef makeEntityRef(Property const& _from, Property const& _to) const;

        std::optional<Property> getParentEntity(Property const& _node) const; ///< Get the parent Entity Property

        /// Load a file into a Property
        ///
        /// The Property and its prefabs will share json data with other loaded Property
        Property loadProperty(char const* _schemaName, char const* _filepath);

        /// Load a file into a Property
        ///
        /// The Property and its prefabs will share json data with other loaded Property
        /// @remark The Schema is auto-detected
        Property loadProperty(char const* _filepath);

        /// Load and copy file into a Property
        ///
        /// The Property will not share its json data with other loaded Properties.
        /// It is considered as a new file.
        /// However, the prefabs are not copied and still share their data with other Properties.
        Property loadPropertyCopy(char const* _schemaName, char const* _filepath);

        /// Load and copy file into a Property
        ///
        /// The Property will not share its json data with other loaded Properties.
        /// It is considered as a new file.
        /// However, the prefabs are not copied and still share their data with other Properties.
        Property loadPropertyCopy(char const* _filepath);

        /// Create a new empty document with the given Schema
        Property newProperty(Subschema const* _schema);

        VersionedJson& readJsonFile(char const* _filepath) const;
        VersionedJson& createTempJsonFile(char const* _schemaName) const;
        void saveJsonFile(nlohmann::json const* doc, char const* _filepath, char const* _schema) const;

        // Warning : this function changes the current directory temporarily and restores it at the end of the function
        void saveJsonFileDatabase(char const* _customRootpath) const;

        std::vector<std::pair<std::filesystem::path, JSonFileState>> collectOutdatedJsonFiles() const;
        void reloadJsonFiles(std::vector<std::filesystem::path> const& _filePaths) const;

        void setFallBackEntityPath(char const* _filepath);
        char const* getFallBackEntityPath() const;

        using NewDepFileCallback = std::function<void(char const*)>;

        /// Set a callback to be informed when EntityLin load a file. Useful to list dependencies.
        void setNewDepFileCallBack(NewDepFileCallback _callback);

        /// It is incremented each time a document is changed.
        /// So it is the version of the "document database".
        size_t getGlobalDocumentsVersion() const;

        void incrementGlobalDocumentsVersion();

        bool getRebuildPropertyEnabled() const;

        void setRebuildPropertyEnabled(bool _rebuildPropertyEnabled);

    private:
        /// Load an Entity or a Scene, using the given cache
        template <typename Type, typename Cache, typename ValidateFunc, typename LoadFunc>
        std::shared_ptr<Type const> loadEntityOrScene(
            std::filesystem::path const& _path,
            Cache& cache,
            ValidateFunc&& validate,
            LoadFunc&& load,
            Type const* _super) const;

        mutable std::unordered_map<std::filesystem::path, std::unique_ptr<VersionedJson>, HashPath>
            m_jsonDatabase;
        mutable std::vector<std::unique_ptr<VersionedJson>> m_tempJsonFiles;
        String m_fallbackEntity;
        NewDepFileCallback m_newDepFileCallback;
        size_t m_globalDocumentsVersion = 0;
        bool m_rebuildPropertyEnabled = true;
    };

} // namespace Ent
