#pragma once

#include <functional>

#pragma warning(push)
#pragma warning(disable : 4464)
#include "../Override.h"
#include "../RemovableMap.h"
#include "../Array.h"
#include "../MemoryProfiler.h"
#include "../Union.h"
#include "../Object.h"
#include "../Node.h"
#include "../PropImpl.h"
#pragma warning(pop)

namespace Ent
{
    struct Node;
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
        mutable Pool<Node> nodePool;
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

        /// Load the Node at path _nodeSchema then return a pointer to the cached data
        std::shared_ptr<Node const> loadNodeReadOnly(
            Subschema const& _nodeSchema, char const* _nodePath, Node const* _super = nullptr) const;

        /// Load the Node at path _nodeSchema then return a pointer to the cached data
        std::shared_ptr<Node const> loadNodeEntityReadOnly(char const* _nodePath) const;

        /// Load an entity file into a Node
        NodeUniquePtr loadEntityAsNode(std::filesystem::path const& _entityPath) const;

        /// Load a scene file into a Node
        NodeUniquePtr loadSceneAsNode(std::filesystem::path const& _scenePath) const;

        /// Load any entitylib file into a Node, giving a schema
        NodeUniquePtr loadFileAsNode(std::filesystem::path const& _path, Subschema const& _schema) const;

        /// Load any entitylib file into a Node, reading the schema name inside the file
        NodeUniquePtr loadFileAsNode(std::filesystem::path const& _nodePath) const;

        /// Save the Entity at path _entityPath
        void saveNodeAsEntity(Node const* _entity, char const* _relEntityPath) const;

        /// Save the Scene at path _scenePath
        void saveNodeAsScene(Node const* _scene, char const* _scenePath) const;

        /// Dump the given Node with the given schema in json format
        static nlohmann::json dumpNode(
            Subschema const& _schema, ///< Schema for the Node
            Node const& _node, ///< the Node to dump
            OverrideValueSource _dumpedValueSource =
                OverrideValueSource::Override, ///< Dump only fields with given value source
            bool _superKeyIsTypeName =
                false, ///< Super sub-node are dumped using their type name for key instead of "Super"
            std::function<void(EntityRef&)> const& _entityRefPreProc = {},
            bool _saveUnionIndex = false,
            bool _forceWriteKey = false);

        /// Instanciate the given _prefab Node
        NodeUniquePtr makeNodeInstanceOf(
            char const* _schemaName, ///< Name of the schema
            char const* _prefab ///< Path to the prefab Entity
        ) const;

        /// Instanciate the given _prefab Entity
        NodeUniquePtr makeEntityNodeInstanceOf(char const* _prefab ///< Path to the prefab Entity
        ) const;

        /// Create a Node with the given _schemaName
        NodeUniquePtr makeNode(char const* _schemaName) const;

        NodeUniquePtr newNode(Node::Value val, Subschema const* _subschema) const;

        /// Create a Node with the Entity's schema
        NodeUniquePtr makeEntityNode() const;

        struct NodeFile
        {
            std::shared_ptr<Node> data;
            std::filesystem::file_time_type time;
        };
        std::map<std::filesystem::path, NodeFile> const& getNodeCache() const;
        struct HashPath
        {
            auto operator()(std::filesystem::path const& p) const;
        };
        std::unordered_map<std::filesystem::path, std::unique_ptr<VersionedJson>, HashPath> const&
        getJsonDatabase() const;

        void clearCache() const;

        std::filesystem::path getAbsolutePath(std::filesystem::path const& _path) const;
        /// @param _path : A file path absolute or relative but inside the rawdata path
        std::filesystem::path getRelativePath(std::filesystem::path const& _path) const;

        NodeUniquePtr loadNode(
            Subschema const& _nodeSchema,
            nlohmann::json const& _data,
            Node const* _super,
            nlohmann::json const* _default = nullptr) const;

        /// @brief Resolve an EntityRef relative to this Node/Entity.
        /// Returns nullptr in case of failure.
        Node const* resolveEntityRef(Node const* _node, EntityRef const& _entityRef) const;
        /// @brief Resolve an EntityRef relative to this Node/Entity.
        /// Returns nullptr in case of failure.
        Node* resolveEntityRef(Node* _node, EntityRef const& _entityRef) const;

        Subschema const* getSchema(char const* _schemaName) const;
        Subschema const* getEntitySchema() const;
        Subschema const* getSceneSchema() const;

        void setLogicErrorPolicy(LogicErrorPolicy _LogicErrorPolicy);
        LogicErrorPolicy getLogicErrorPolicy() const;
        /// @brief Compute the EntityRef going from the Entity _from, to the Entity _to
        /// @pre _from and _to are Entity nodes
        EntityRef makeEntityRef(Node const& _from, Node const& _to) const;

        /// @brief Resolve an EntityRef relative to this Node/Entity.
        /// Returns nullptr in case of failure.
        std::optional<Property> resolveEntityRef(Property const& _node, EntityRef const& _entityRef) const;
        /// @brief Compute the EntityRef going from the Entity _from, to the Entity _to
        /// @pre _from and _to are Entity nodes
        EntityRef makeEntityRef(Property const& _from, Property const& _to) const;

        Node* getParentEntity(Node* _node) const; ///< Get the parent Entity Node
        Node const* getParentEntity(Node const* _node) const; ///< Get the parent Entity Node
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

        NodeUniquePtr loadObject(
            Subschema const& _nodeSchema,
            nlohmann::json const& _data,
            Node const* _super,
            nlohmann::json const* _default = nullptr,
            bool _ignoreInstanceOf = false) const;

        NodeUniquePtr loadUnion(
            Subschema const& _nodeSchema,
            nlohmann::json const& _data,
            Node const* _super,
            nlohmann::json const* _default = nullptr) const;

        NodeUniquePtr loadArray(
            Subschema const& _nodeSchema,
            nlohmann::json const& _data,
            Node const* _super,
            nlohmann::json const* _default = nullptr) const;

        NodeUniquePtr loadPrimitive(
            Subschema const& _nodeSchema,
            nlohmann::json const& _data,
            Node const* _super,
            nlohmann::json const* _default = nullptr) const;

        mutable std::map<std::filesystem::path, NodeFile> m_nodeCache;

        mutable std::unordered_map<std::filesystem::path, std::unique_ptr<VersionedJson>, HashPath>
            m_jsonDatabase;
        mutable std::vector<std::unique_ptr<VersionedJson>> m_tempJsonFiles;
        String m_fallbackEntity;
        NewDepFileCallback m_newDepFileCallback;
        size_t m_globalDocumentsVersion = 0;
        bool m_rebuildPropertyEnabled = true;
    };

} // namespace Ent
