#pragma once

#include <memory>

#pragma warning(push)
#pragma warning(disable : 4464)
#include "Override.h"
#include "include/EntityLibCore.h"
#include "Scene.h"
#pragma warning(pop)

namespace Ent
{
    struct Node;
    struct Scene;
    struct MemoryProfiler;
    class EntityLib;

    /// @brief The properties of a component "SubScene"
    /// @remark "SubScene" need a special case because it contain some Scene, although a Node can't be a Scene.
    ///  There are other solutions to sove this problem like keep everything as a Node and make
    ///  Scene/Component only wrapper to Node. Let's see if the current solution is ok.
    /// @todo : Make all fields private since this struct has some invariants
    struct SubSceneComponent
    {
        size_t index = 0; ///< Useful to keep the components order in the json file
        std::unique_ptr<Scene> embedded; ///< Embedded Scene, when isEmbedded is true
        bool hasPrefab = false;

        void computeMemory(MemoryProfiler& prof) const;

        /// @cond PRIVATE
        explicit SubSceneComponent(
            EntityLib const* _entlib,
            bool _hasPrefab,
            size_t _index = 0,
            std::unique_ptr<Scene> _embedded = {});
        SubSceneComponent(SubSceneComponent const&) = delete;
        SubSceneComponent(SubSceneComponent&&) noexcept = delete;
        SubSceneComponent& operator=(SubSceneComponent const&) = delete;
        SubSceneComponent& operator=(SubSceneComponent&&) noexcept = delete;
        DeleteCheck deleteCheck;
        /// @brief Create a SubSceneComponent which instanciate this one. (internal use only)
        std::unique_ptr<SubSceneComponent> makeInstanceOf() const;
        /// @endcond PRIVATE

        /// @brief Recursively check if there is an override inside.
        bool hasOverride() const;

        std::unique_ptr<SubSceneComponent> clone() const; ///< Clone this SubSceneComponent identically

        /// @brief detach the Scene from this sub scene components, leaving the embedded sub scene empty
        /// @pre this SubScene is embedded, i.e. isEmbedded is true
        std::unique_ptr<Scene> detachEmbedded();

        /// @brief Take all values set in this and set them into \b _dest
        void applyAllValues(SubSceneComponent& _dest, CopyMode _copyMode) const;
    };

} // namespace Ent
