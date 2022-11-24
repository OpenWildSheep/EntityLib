#pragma once

#include <vector>

#include "Visitor.h"
#include "Property.h"

namespace Ent
{
    /// Deep copy from a Node to an empty Node
    class SearchProperty : public RecursiveVisitor
    {
        std::string m_pattern;
        std::vector<Property> m_foundProperties;

        std::string m_tempStr;

        static void _lowerString(std::string& _str)
        {
            std::transform(
                begin(_str),
                end(_str),
                begin(_str),
                [](char c) { return static_cast<char>(std::tolower(c)); });
        }

        void _testMatch(Property const& _source, char const* _name)
        {
            m_tempStr = _name;
            _lowerString(m_tempStr);
            if (m_tempStr.find(m_pattern) != std::string::npos)
            {
                m_foundProperties.push_back(_source);
            }
        }

        void _testMatch(Property const& _source, int64_t _name)
        {
            _testMatch(_source, std::to_string(_name).c_str());
        }

    public:
        SearchProperty(char const* _pattern)
            : m_pattern(_pattern)
        {
            _lowerString(m_pattern);
        }

        std::vector<Property> const& getMatchingProperties() const
        {
            return m_foundProperties;
        }

        bool inObjectField([[maybe_unused]] Property& _source, char const* _key) override
        {
            _testMatch(_source, _key);
            return true;
        }
        void inUnion(Property& _source, char const* _type) override
        {
            _testMatch(_source, _type);
        }
        void inMapElement([[maybe_unused]] Property& _source, char const* _key) override
        {
            _testMatch(_source, _key);
        }
        void inMapElement([[maybe_unused]] Property& _source, int64_t _key) override
        {
            _testMatch(_source, _key);
        }
        void inArrayElement([[maybe_unused]] Property& _source, size_t _index) override
        {
            _testMatch(_source, static_cast<int64_t>(_index));
        }
        void key([[maybe_unused]] Property& _source, char const* _key) override
        {
            _testMatch(_source, _key);
        }
        void key([[maybe_unused]] Property& _source, int64_t _key) override
        {
            _testMatch(_source, std::to_string(_key).c_str());
        }
        void inUnionSetElement(Property& _source, char const* _type) override
        {
            _testMatch(_source, _type);
        }
        void inObjectSetElement([[maybe_unused]] Property& _source, char const* _key) override
        {
            _testMatch(_source, _key);
        }
        void inObjectSetElement([[maybe_unused]] Property& _source, int64_t _key) override
        {
            _testMatch(_source, _key);
        }
    };
} // namespace Ent
