#pragma once

#include "../external/json.hpp" // TODO : Remove when the rawData in Component is no more useful
#include "../Node.h"

namespace Ent
{
    // ******************************** Implem details ********************************************

    struct Node;

    // *********************************** Scene/Entity/Component ****************************

    /// The properties of a given component
    struct Component
    {
        nlohmann::json rawData;
        std::string type; ///< Component type (ex : Transform, VisualGD, HeightObj ...)
        Node root; ///< Root node of the component. Always of type Ent::DataType::object
        size_t version{}; ///< @todo remove?
        size_t index{}; ///< Useful to keep the componants order in the json file. To make diffs easier.
        DeleteCheck deleteCheck;
        bool hasPrefab{}; ///< True if it overrides an other component (not just default)

        Component(
            nlohmann::json _rawData,
            bool _hasPrefab,
            std::string _type,
            Node _root,
            size_t _version,
            size_t _index);

        /// \cond PRIVATE
        void computeMemory(MemoryProfiler& prof) const;

        /// Create a Component which is an "instance of" this one. With no override.
        Component makeInstanceOf() const;
        /// \endcond

        /// @brief Recursively check if there is an override inside.
        bool hasOverride() const;
        /// @brief Recursively check if values are at default value.
        bool hasDefaultValue() const;
        /// Is this component used in runtime engine ?
        bool isUsedInRuntime() const;
        /// Is this component used in editors ?
        bool isUsedInEditor() const;

        /// @brief Take all values set in this and set them into \b _dest
        /// @pre \b _dest has the same component type than \b this
        void applyAllValues(Component& _dest, CopyMode _copyMode) const;
    };

} // namespace Ent
