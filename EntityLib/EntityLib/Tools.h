#pragma once

#pragma warning(push, 0)
#include <filesystem>

#include "../external/json.hpp"
#pragma warning(pop)

namespace std
{
    using namespace experimental;
} // namespace std

nlohmann::json loadJsonFile(std::filesystem::path const& path);

namespace Ent
{
    char const* getRefTypeName(char const* link);

    std::vector<std::string> splitString(const std::string& _str, char _delimiter);

    std::string computeRelativePath(std::vector<std::string> _fromAbsolute, 
        std::vector<std::string> _toAbsolute, bool _leavesAreLast = true);
}
