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
