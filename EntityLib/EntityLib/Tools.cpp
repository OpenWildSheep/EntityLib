#include "Tools.h"

#include <fstream>
#include <sstream>

using namespace nlohmann;

json loadJsonFile(std::filesystem::path const& path)
{
    std::ifstream file(path);
    if (not file.is_open())
    {
        throw std::runtime_error("Can't open file for read: " + path.u8string());
    }
    json doc;
    file >> doc;
    return doc;
};

char const* Ent::getRefTypeName(char const* link)
{
    // Force to create the definition (do nothing if already exist)
    static char const* definitionsStr = "#/definitions/";
    auto const defPos = strstr(link, definitionsStr);
    if (defPos == nullptr)
    {
        return nullptr;
    }
    return defPos + strlen(definitionsStr);
}

std::vector<std::string> Ent::splitString(const std::string& _str, char _delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(_str);
    while (std::getline(tokenStream, token, _delimiter))
    {
        if (not token.empty())
        {
            tokens.push_back(token);
        }
    }
    return tokens;
}
