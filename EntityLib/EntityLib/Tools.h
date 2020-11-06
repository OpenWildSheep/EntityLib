#pragma once

#pragma warning(push, 0)
#include "external/json.hpp"
#include "external/filesystem.hpp"
#pragma warning(pop)

nlohmann::json loadJsonFile(std::filesystem::path const& _path);

namespace Ent
{
    /// @cond PRIVATE
    /// @brief Given a link to a definition, get the name of the definition.
    ///
    /// Example : "file://EditionComponents.json#/definitions/HeightObj" => "HeightObj"
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
        std::size_t constexpr operator()(char const* input) const
        {
            return *input ? static_cast<unsigned int>(*input) + 33 * (*this)(input + 1) : 5381;
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
    /// @endcond PRIVATE
} // namespace Ent
