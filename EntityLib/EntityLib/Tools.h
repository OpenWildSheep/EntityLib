#pragma once

#pragma warning(push, 0)
#include "external/json.hpp"
#include "external/filesystem.hpp"
#pragma warning(pop)

nlohmann::json loadJsonFile(std::filesystem::path const& _root, std::filesystem::path const& _rel);

namespace Ent
{
    /// @cond PRIVATE
    /// @brief Given a link to a definition, get the name of the definition.
    ///
    /// Example : "./EditionComponents.json#/definitions/HeightObj" => "HeightObj"
    char const* getRefTypeName(char const* link);

    std::vector<std::string>
    splitString(const std::string& _str, char _delimiter, bool _keepEmptyToken = false);

    /// @brief Given two absolute path,
    ///   compute the shorter relative path to go from _fromAbsolute to _toAbsolute
    /// @param _leavesAreLast is true if the path is in the "usual" order. From root to leaves.\n
    ///     _leavesAreLast is false if the path is in the "reverse" order. From leaves to root.
    /// @remark Used for EntityRef
    std::string computeRelativePath(
        std::vector<std::string> _fromAbsolute,
        std::vector<std::string> _toAbsolute,
        bool _leavesAreLast = true);

    template <class>
    struct hasher;
    template <>
    struct hasher<std::string>
    {
        uint32_t constexpr HashStrRecur(uint32_t _hash, const char* _str) const
        {
            return (*_str == 0) ? _hash : HashStrRecur(((_hash << 5) + _hash) + *_str, _str + 1);
        }

        std::size_t constexpr operator()(char const* _str) const
        {
            return (*_str == 0) ? 0 : HashStrRecur(5381, _str);
        }
        std::size_t operator()(const std::string& str) const
        {
            return (*this)(str.c_str());
        }
    };
    template <typename T>
    std::size_t constexpr hash(T&& t)
    {
        return hasher<typename std::decay<T>::type>()(std::forward<T>(t));
    }
    inline namespace literals
    {
        std::size_t constexpr operator"" _hash(const char* s, size_t)
        {
            return hasher<std::string>()(s);
        }
    } // namespace literals

    inline std::string strToLower(std::string s)
    {
        std::transform(
            s.begin(), s.end(), s.begin(), [](unsigned char c) { return char(std::tolower(c)); });
        return s;
    }
    /// @endcond PRIVATE
} // namespace Ent
