#pragma once

#include <vector>

#include "Visitor.h"
#include "Property.h"

namespace Ent
{
    /// Dump a Property to a nlohmann::json
    class DumpProperty final : public RecursiveVisitor
    {
    public:
        explicit DumpProperty(
            nlohmann::json& _dest, ///< output json node
            bool _superKeyIsTypeName = false ///< Replace the "Super" field with the field's type
            )
            : m_dest(_dest)
            , m_superKeyIsTypeName(_superKeyIsTypeName)
        {
            _Push(m_dest);
        }
        void inObject([[maybe_unused]] Property& _source) override
        {
            _Back() = nlohmann::json::object();
        }
        bool inObjectField([[maybe_unused]] Property& _source, char const* _key) override
        {
            if (_DoNeedCopy(_source))
            {
                if (m_superKeyIsTypeName && strcmp(_key, "Super") == 0)
                {
                    _key = _source.getSchema()->name.c_str();
                }
                _Push(_Back()[_key]);
                return true;
            }
            return false;
        }
        void outObjectField([[maybe_unused]] Property& _source, [[maybe_unused]] char const* _key) override
        {
            _Pop();
        }
        void inUnion(Property& _source, char const* _type) override
        {
            _Back() = nlohmann::json::object();
            _Back()[_source.getSchema()->getUnionNameField()] = _type;
            _Push(_Back()[_source.getSchema()->getUnionDataField()]);
        }
        void outUnion([[maybe_unused]] Property& _source) override
        {
            _Pop();
        }
        void inMap([[maybe_unused]] Property& _source) override
        {
            _Back() = nlohmann::json::array();
        }
        void inMapElement([[maybe_unused]] Property& _source, char const* _key) override
        {
            auto&& newPair = _Back().emplace_back(nlohmann::json::array());
            newPair.emplace_back(_key);
            _Push(newPair.emplace_back(nlohmann::json::object()));
        }
        void inMapElement([[maybe_unused]] Property& _source, int64_t _key) override
        {
            auto&& newPair = _Back().emplace_back(nlohmann::json::array());
            newPair.emplace_back(_key);
            _Push(newPair.emplace_back(nlohmann::json::object()));
        }
        void outMapElement([[maybe_unused]] Property& _source) override
        {
            _Pop();
        }
        void inArrayElement([[maybe_unused]] Property& _source, size_t _index) override
        {
            _Push(_Back().emplace_back(_index));
        }
        void outArrayElement([[maybe_unused]] Property& _source) override
        {
            _Pop();
        }
        void inPrimSet([[maybe_unused]] Property& _prop, [[maybe_unused]] DataType _dataType) override
        {
            _Back() = nlohmann::json::array();
        }
        void inObjectSet([[maybe_unused]] Property& _prop) override
        {
            _Back() = nlohmann::json::array();
        }
        void inUnionSet([[maybe_unused]] Property& _prop) override
        {
            _Back() = nlohmann::json::array();
        }
        void key([[maybe_unused]] Property& _source, char const* _key) override
        {
            _Back().push_back(_key);
        }
        void key([[maybe_unused]] Property& _source, int64_t _key) override
        {
            _Back().push_back(_key);
        }
        void inUnionSetElement(Property& _source, char const* _type) override
        {
            auto& newElt = _Back().emplace_back(nlohmann::json::object());
            auto const& itemSchema = _source.getParent()->getSchema()->singularItems->get();
            newElt[itemSchema.getUnionNameField()] = _type;
            _Push(newElt[itemSchema.getUnionDataField()]);
        }
        void outUnionSetElement([[maybe_unused]] Property& _source) override
        {
            _Pop();
        }
        void inObjectSetElement([[maybe_unused]] Property& _source, [[maybe_unused]] char const* _key) override
        {
            _Push(_Back().emplace_back(nlohmann::json::object()));
        }
        void inObjectSetElement([[maybe_unused]] Property& _source, [[maybe_unused]] int64_t _key) override
        {
            _Push(_Back().emplace_back(nlohmann::json::object()));
        }
        void outObjectSetElement([[maybe_unused]] Property& _source) override
        {
            _Pop();
        }
        void inArray([[maybe_unused]] Property& _source) override
        {
            _Back() = nlohmann::json::array();
        }
        void boolProperty(Property& _source) override
        {
            _Back() = _source.getBool();
        }
        void intProperty(Property& _source) override
        {
            _Back() = _source.getInt();
        }
        void floatProperty(Property& _source) override
        {
            _Back() = _source.getFloat();
        }
        void stringProperty(Property& _source) override
        {
            _Back() = _source.getString();
        }
        void entityRefProperty(Property& _source) override
        {
            _Back() = _source.getEntityRef().entityPath;
        }

    private:
        [[nodiscard]] nlohmann::json& _Back()
        {
            return *m_stack.back();
        }

        void _Push(nlohmann::json& _prop)
        {
            m_stack.push_back(&_prop);
        }

        void _Pop()
        {
            m_stack.pop_back();
        }

        [[nodiscard]] static bool _DoNeedCopy(Property const& _source)
        {
            return _source.hasOverride();
        }

        nlohmann::json& m_dest;
        std::vector<nlohmann::json*> m_stack;
        bool m_superKeyIsTypeName = false;
    };
} // namespace Ent
