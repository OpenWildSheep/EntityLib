#pragma once

#pragma warning(push)
#pragma warning(disable : 4464)
#include "../Override.h"
#include "../RemovableMap.h"
#include "../Array.h"
#include "../MemoryProfiler.h"
#include "../Union.h"
#include "../Object.h"
#include "../Node.h"
#include "../Component.h"
#include "../Scene.h"
#include "../Entity.h"
#include "../SubSceneComponent.h"
#pragma warning(pop)

namespace Ent
{
    struct Node;
    struct Scene;
    class EntityLib;
    struct Entity;

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

    /// Entry point of the EntityLib. Used to load/save Scene/Entity and to parse the Schema
    class ENTLIB_DLLEXPORT EntityLib
    {
    public:
        mutable Pool<Node> nodePool;
        /// @todo Make public attribute private?
        std::filesystem::path rootPath; ///< Path to the perforce root (X:/)
        std::filesystem::path rawdataPath; ///< Path to the RawData dir in the perforce root (X:/RawData)
        std::filesystem::path toolsDir; ///< Path to the Tools dir in in the perforce root (X:/Tools)
        ComponentsSchema schema; ///< Schema of all components
        bool validationEnabled = false; ///< validate all objects at load/save

        /// Component needed for each type of components
        std::map<std::string, std::vector<std::string>> componentDependencies;

        /// Load the EntityLib, given the path to the Tools directory
        explicit EntityLib(std::filesystem::path const& _rootPath, bool _doMergeComponents = false);
        ~EntityLib();
        /// @cond PRIVATE
        EntityLib(EntityLib const&) = delete;
        EntityLib& operator=(EntityLib const&) = delete;
        DeleteCheck deleteCheck;
        /// @endcond

        /// Load the Entity at path _entityPath then return a pointer to the cached data
        std::shared_ptr<Entity const> loadEntityReadOnly(
            std::filesystem::path const& _entityPath, Ent::Entity const* _super = nullptr) const;

        /// Load the Scene at path _scenePath then return a pointer to the cached data
        std::shared_ptr<Scene const> loadSceneReadOnly(std::filesystem::path const& _scenePath) const;

        /// Load the Node at path _nodeSchema then return a pointer to the cached data
        std::shared_ptr<Node const> loadNodeReadOnly(
            Ent::Subschema const& _nodeSchema,
            char const* _nodePath,
            Ent::Node const* _super = nullptr) const;

        /// Load the Node at path _nodeSchema then return a pointer to the cached data
        std::shared_ptr<Node const> loadNodeEntityReadOnly(char const* _nodePath) const;

        /// Load the Scene in legacy format at path _scenePath then return a pointer to the cached data
        std::shared_ptr<Scene const>
        loadLegacySceneReadOnly(std::filesystem::path const& _scenePath) const;

        /// Load an entity file into a Node
        NodeUniquePtr loadEntityAsNode(std::filesystem::path const& _entityPath) const;

        /// Load a scene file into a Node
        NodeUniquePtr loadSceneAsNode(std::filesystem::path const& _scenePath) const;

        /// Load any entitylib file into a Node, giving a schema
        NodeUniquePtr
        loadFileAsNode(std::filesystem::path const& _path, Ent::Subschema const& _schema) const;

        /// Load the Entity at path _entityPath
        std::unique_ptr<Entity> loadEntity(
            std::filesystem::path const& _entityPath, Ent::Entity const* _super = nullptr) const;

        std::unique_ptr<Ent::Entity> loadEntityFromJson(
            nlohmann::json const& _entNode, Ent::Entity const* _superEntityFromParentEntity) const;

        /// Load the Scene at path _scenePath
        std::unique_ptr<Scene> loadScene(std::filesystem::path const& _scenePath) const;

        /// Load the Scene in legacy format at path _scenePath
        std::unique_ptr<Scene> loadLegacyScene(std::filesystem::path const& _scenePath) const;

        /// Save the Entity at path _entityPath
        void saveEntity(Entity const& _entity, std::filesystem::path const& _relEntityPath) const;

        /// Save the Scene at path _scenePath
        void saveScene(Scene const& _scene, std::filesystem::path const& _scenePath) const;

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

        /// @brief Create an Entity which instanciate an other.
        ///
        /// This allow to override some properties without change the prefab properties.
        std::unique_ptr<Entity> makeInstanceOf(std::string const& _instanceOf ///< Path to the prefab Entity
        ) const;

        struct EntityFile
        {
            std::shared_ptr<Entity> data;
            std::filesystem::file_time_type time;
        };
        struct SceneFile
        {
            std::shared_ptr<Scene> data;
            std::filesystem::file_time_type time;
        };
        struct NodeFile
        {
            std::shared_ptr<Node> data;
            std::filesystem::file_time_type time;
        };
        std::map<std::filesystem::path, EntityFile> const& getEntityCache() const;
        std::map<std::filesystem::path, SceneFile> const& getSceneCache() const;
        std::map<std::filesystem::path, NodeFile> const& getNodeCache() const;

        void clearCache();

        std::filesystem::path getAbsolutePath(std::filesystem::path const& _path) const;
        /// @param _path : A file path absolute or relative but inside the rawdata path
        std::filesystem::path getRelativePath(std::filesystem::path const& _path) const;

        std::unique_ptr<Ent::Node> loadNode(
            Ent::Subschema const& _nodeSchema,
            nlohmann::json const& _data,
            Ent::Node const* _super,
            nlohmann::json const* _default = nullptr) const;

        /// @brief Resolve an EntityRef relative to this Node/Entity.
        /// Returns nullptr in case of failure.
        Node const* resolveEntityRef(Node const* _node, const EntityRef& _entityRef) const;
        /// @brief Resolve an EntityRef relative to this Node/Entity.
        /// Returns nullptr in case of failure.
        Node* resolveEntityRef(Node* _node, const EntityRef& _entityRef) const;

        Subschema const* getSchema(char const* _schemaName) const;
        Subschema const* getEntitySchema() const;
        Subschema const* getSceneSchema() const;

        void setLogicErrorPolicy(LogicErrorPolicy _LogicErrorPolicy);
        LogicErrorPolicy getLogicErrorPolicy() const;
        /// @brief Compute the EntityRef going from the Entity _from, to the Entity _to
        /// @pre _from and _to are Entity nodes
        EntityRef makeEntityRef(Node const& _from, Node const& _to);

        Node* getParentEntity(Node* _node); ///< Get the parent Entity Node
        Node const* getParentEntity(Node const* _node); ///< Get the parent Entity Node

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
            Ent::Subschema const& _nodeSchema,
            nlohmann::json const& _data,
            Ent::Node const* _super,
            nlohmann::json const* _default = nullptr) const;

        NodeUniquePtr loadUnion(
            Ent::Subschema const& _nodeSchema,
            nlohmann::json const& _data,
            Ent::Node const* _super,
            nlohmann::json const* _default = nullptr) const;

        NodeUniquePtr loadArray(
            Ent::Subschema const& _nodeSchema,
            nlohmann::json const& _data,
            Ent::Node const* _super,
            nlohmann::json const* _default = nullptr) const;

        NodeUniquePtr loadPrimitive(
            Ent::Subschema const& _nodeSchema,
            nlohmann::json const& _data,
            Ent::Node const* _super,
            nlohmann::json const* _default = nullptr) const;

        mutable std::map<std::filesystem::path, EntityFile> m_entityCache;
        mutable std::map<std::filesystem::path, SceneFile> m_sceneCache;
        mutable std::map<std::filesystem::path, NodeFile> m_nodeCache;
    };

} // namespace Ent
