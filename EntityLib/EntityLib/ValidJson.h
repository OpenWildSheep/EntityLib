#pragma once

#pragma warning(push, 0)
#include <filesystem>

#include "../external/json.hpp" // TODO : Try to remove this inclusion
#pragma warning(pop)

namespace std
{
    using namespace experimental;
} // namespace std

namespace Ent
{
    void validScene(std::filesystem::path toolsDir, nlohmann::json const& scene);
    void validEntity(std::filesystem::path toolsDir, nlohmann::json const& entity);
} // namespace Ent
