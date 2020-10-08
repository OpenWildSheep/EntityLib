#pragma once

#pragma warning(push, 0)
#include <filesystem>

#include "../external/json.hpp"
#pragma warning(pop)

namespace std
{
    using namespace experimental;
} // namespace std

nlohmann::json loadJsonFile(std::filesystem::path const& _path);

namespace Ent
{
    /// @cond PRIVATE
    /// @brief Given a link to a definition, get the name of the definition.
    ///
    /// Example : "file://EditionComponents.json#/definitions/HeightObj" => "HeightObj"
    char const* getRefTypeName(char const* link);

    std::vector<std::string> splitString(const std::string& _str, char _delimiter);

    /// @brief Given two absolute path,
    ///   compute the shorter relative path to go from _fromAbsolute to _toAbsolute
    /// @param _leavesAreLast is true if the path is in the "usual" order. From root to leaves.\n
    ///     _leavesAreLast is false if the path is in the "reverse" order. From leaves to root.
    /// @remark Used for EntityRef
    std::string computeRelativePath(
        std::vector<std::string> _fromAbsolute,
        std::vector<std::string> _toAbsolute,
        bool _leavesAreLast = true);
    /// @endcond PRIVATE
} // namespace Ent
