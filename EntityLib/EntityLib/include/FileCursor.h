#pragma once

#include "EntityLib.h"
#include <variant>
#include <ciso646>
#include "../Tools.h"

namespace Ent
{

    struct CmpStr
    {
        bool operator()(char const* a, char const* b) const
        {
            return strcmp(a, b) < 0;
        }
    };

    struct ENTLIB_DLLEXPORT FileCursor
    {
        using Key = std::variant<char const*, size_t>;
        struct Schema
        {
            Ent::Subschema const* base = nullptr;
            nlohmann::json const* propDefVal = nullptr; ///< Property default values
        };
        struct Layer
        {
            Schema schema;
            nlohmann::json* values{};
            Key additionalPath;
        };

        FileCursor();

        FileCursor(Ent::Subschema const* _schema, char const* m_filePath, nlohmann::json* _document);

        void init(Ent::Subschema const* _schema, char const* _filePath, nlohmann::json* _document);

        Layer* layerBegin();

        Layer* layerEnd();

        Layer& lastLayer();

        Layer const& lastLayer() const;

        size_t layerCount() const;

        void clear();

        FileCursor(Ent::Subschema const* _schema, char const* m_filePath);

        void pushBack(char const* key);

        void pushBack(int64_t key);

        void save(char const* _filename = nullptr) const;

        nlohmann::json* back();

        nlohmann::json const* back() const;

        // IsSet but can be null
        bool isSetInternal() const;

        bool isSet() const;

        bool isNull() const;

        FileCursor& enterObjectField(char const* _field, SubschemaRef const* _fieldRef = nullptr);

        FileCursor& enterUnionSetItem(char const* _field, Subschema const* _dataSchema = nullptr);

        FileCursor& enterObjectSetItem(char const* _field);

        FileCursor& enterObjectSetItem(int64_t _field);

        FileCursor& enterMapItem(char const* _field);

        FileCursor& enterMapItem(int64_t _field);

        FileCursor& enterArrayItem(size_t index);

        char const* getUnionType() const;

        std::pair<Ent::Subschema const*, nlohmann::json const*> getUnionData();

        FileCursor& enterUnionData(char const* _unionType);

        FileCursor& exit();

        Subschema const* getSchema() const;

        nlohmann::json const* getPropertyDefaultValue() const;

        static void setLayer(Layer& lastSet, Layer& firstNotSet, size_t arraySize);

        void setSize(size_t size);
        void setFloat(double value);
        void setInt(int64_t value);
        void setString(char const* value);
        void setBool(bool value);
        void setEntityRef(EntityRef const& value);
        static nlohmann::json& getOrCreate(nlohmann::json& val, char const* field);
        void setUnionType(char const* type);
        double getFloat() const;
        int64_t getInt() const;
        //size_t size(size_t layerIndex = size_t(-1)) const
        //{
        //    if (layerIndex == size_t(-1))
        //    {
        //        layerIndex = m_layers.size() - 1;
        //    }
        //    return m_layers[layerIndex].values->size();
        //}
        char const* getString() const;
        bool getBool() const;
        EntityRef getEntityRef() const;

    private:
        std::string m_filePath;
        std::vector<Layer> m_layers;
        nlohmann::json* m_rootDoc = nullptr;
    };

} // namespace Ent
