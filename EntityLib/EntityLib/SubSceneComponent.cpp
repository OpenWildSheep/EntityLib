#include "SubSceneComponent.h"

#include <ciso646>

#include "MemoryProfiler.h"

#include "Scene.h"
#include "include/EntityLib.h"

namespace Ent
{
    SubSceneComponent::SubSceneComponent(
        EntityLib const* _entlib, bool _hasPrefab, size_t _index, std::unique_ptr<Scene> _embedded)
        : index(_index)
        , embedded(std::move(_embedded))
        , hasPrefab(_hasPrefab)
    {
        if (embedded == nullptr)
        {
            embedded = std::make_unique<Scene>(_entlib);
        }
    }

    void SubSceneComponent::computeMemory(MemoryProfiler& prof) const
    {
        prof.currentComp.push_back("SubScene");
        if (embedded)
        {
            embedded->computeMemory(prof);
        }
        prof.currentComp.pop_back();
    }

    std::unique_ptr<SubSceneComponent> SubSceneComponent::makeInstanceOf() const
    {
        ENTLIB_ASSERT(embedded != nullptr);
        std::unique_ptr<Scene> instEmbedded = embedded->makeInstanceOf();
        return std::make_unique<SubSceneComponent>(
            embedded->getEntityLib(), true, index, std::move(instEmbedded));
    }

    std::unique_ptr<SubSceneComponent> SubSceneComponent::clone() const
    {
        ENTLIB_ASSERT(embedded != nullptr);
        std::unique_ptr<Scene> instEmbedded = embedded->clone();
        return std::make_unique<SubSceneComponent>(
            embedded->getEntityLib(), hasPrefab, index, std::move(instEmbedded));
    }

    std::unique_ptr<Scene> SubSceneComponent::detachEmbedded()
    {
        auto scene = std::make_unique<Scene>(embedded->getEntityLib());
        std::swap(scene, embedded);

        // we don't to swap owners though
        embedded->setOwnerEntity(scene->getOwnerEntity());
        scene->setOwnerEntity(nullptr); // detached scene is not owned by any entity

        return scene;
    }

    void SubSceneComponent::applyAllValues(SubSceneComponent& _dest, CopyMode _copyMode) const
    {
        if (embedded != nullptr and _dest.embedded != nullptr)
        {
            embedded->applyAllValues(*_dest.embedded, _copyMode);
        }
    }

    bool SubSceneComponent::hasOverride() const
    {
        //if (isEmbedded.isSet())
        //    return true;
        //if (file.isSet())
        //    return true;
        //if (index.isSet())
        //    return true;
        return embedded != nullptr && embedded->hasOverride();
    }
} // namespace Ent
