#include "Tools.h"

#include <fstream>

using namespace nlohmann;

json loadJsonFile(std::filesystem::path const& path)
{
    std::ifstream file(path);
    if (not file.is_open())
    {
        throw std::runtime_error("Can't open file for read: " + path.u8string());
    }
    json doc;
    doc << file;
    return doc;
};

char const* Ent::getRefTypeName(char const* link)
{
    // Force to create the definition (do nothing if already exist)
    static char const* definitionsStr = "#/definitions/";
    auto const defPos = strstr(link, definitionsStr);
    if (defPos == nullptr)
        return nullptr;
    return defPos + strlen(definitionsStr);
}
