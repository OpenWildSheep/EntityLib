#include "include/Cursor.h"

namespace Ent
{
    bool Cursor::isSet() const
    {
        return instance.isSet();
    }

    double Cursor::getFloat() const
    {
        auto& lastLayer = layers.back();
        if (isSet())
        {
            return instance.getFloat();
        }
        else if (lastLayer.prefab != nullptr)
        {
            return lastLayer.prefab->getFloat();
        }
        else if (lastLayer.defaultVal != nullptr and lastLayer.defaultVal->isSet())
        {
            return lastLayer.defaultVal->getFloat();
        }
        else
        {
            return 0.;
        }
    }
    int64_t Cursor::getInt() const
    {
        auto& lastLayer = layers.back();
        if (isSet())
        {
            return instance.getInt();
        }
        else if (lastLayer.prefab != nullptr)
        {
            return lastLayer.prefab->getInt();
        }
        else if (lastLayer.defaultVal != nullptr and lastLayer.defaultVal->isSet())
        {
            return lastLayer.defaultVal->getInt();
        }
        else
        {
            return 0;
        }
    }
    char const* Cursor::getString() const
    {
        auto& lastLayer = layers.back();
        if (isSet())
        {
            return instance.getString();
        }
        else if (lastLayer.prefab != nullptr)
        {
            return lastLayer.prefab->getString();
        }
        else if (lastLayer.defaultVal != nullptr and lastLayer.defaultVal->isSet())
        {
            return lastLayer.defaultVal->getString();
        }
        else if (not getSchema()->enumValues.empty())
        {
            return getSchema()->enumValues.front().c_str();
        }
        else
        {
            return "";
        }
    }
    bool Cursor::getBool() const
    {
        auto& lastLayer = layers.back();
        if (isSet())
        {
            return instance.getBool();
        }
        else if (lastLayer.prefab != nullptr)
        {
            return lastLayer.prefab->getBool();
        }
        else if (lastLayer.defaultVal != nullptr and lastLayer.defaultVal->isSet())
        {
            return lastLayer.defaultVal->getBool();
        }
        else
        {
            return false;
        }
    }
    EntityRef Cursor::getEntityRef() const
    {
        auto& lastLayer = layers.back();
        if (isSet())
        {
            return instance.getEntityRef();
        }
        else if (lastLayer.prefab != nullptr)
        {
            return lastLayer.prefab->getEntityRef();
        }
        else if (lastLayer.defaultVal != nullptr and lastLayer.defaultVal->isSet())
        {
            return lastLayer.defaultVal->getEntityRef();
        }
        else
        {
            return {};
        }
    }
} // namespace Ent
