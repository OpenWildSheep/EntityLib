#include "Tools.h"

#include <fstream>
#include <sstream>
#include <ciso646>

using namespace nlohmann;

/// @cond PRIVATE

json loadJsonFile(std::filesystem::path const& path)
{
    std::ifstream file(path, std::ios::binary);
    if (not file.is_open())
    {
        throw std::runtime_error("Can't open file for read: " + path.u8string());
    }
    std::string data;
    std::getline(file, data, char(0));
    json doc = json::parse(
        data,
        nullptr, // Parser callback
        true, // allow_exceptions
        true // ignore_comments
    );
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

std::string Ent::computeRelativePath(
    std::vector<std::string> _fromAbsolute, std::vector<std::string> _toAbsolute, bool _leavesAreLast)
{
    using PopRootFun = void (*)(std::vector<std::string>&);
    const auto popRoot =
        _leavesAreLast ?
            static_cast<PopRootFun>(
                [](std::vector<std::string>& _path) { _path.erase(_path.begin()); }) :
            static_cast<PopRootFun>([](std::vector<std::string>& _path) { _path.pop_back(); });

    using GetRootFun = std::string& (*)(std::vector<std::string>&);
    const auto getRoot =
        _leavesAreLast ? static_cast<GetRootFun>(
            [](std::vector<std::string>& _path) -> std::string& { return _path.front(); }) :
                         static_cast<GetRootFun>([](std::vector<std::string>& _path) -> std::string& {
                             return _path.back();
                         });

    // remove common ancestors
    while (not _fromAbsolute.empty() and not _toAbsolute.empty()
           and getRoot(_fromAbsolute) == getRoot(_toAbsolute))
    {
        popRoot(_toAbsolute);
        popRoot(_fromAbsolute);
    }

    std::stringstream relativePath;
    // go sufficiently back in hierarchy
    for (size_t i = 0; i < _fromAbsolute.size(); ++i)
    {
        relativePath << "../";
    }

    // then go forward to the target
    const auto appendToPath = [&relativePath](std::string& _pathPart) {
        relativePath << _pathPart << '/';
    };
    if (_leavesAreLast)
    {
        for (auto it = std::begin(_toAbsolute); it != std::end(_toAbsolute); ++it)
        {
            appendToPath(*it);
        }
    }
    else
    {
        for (auto it = std::rbegin(_toAbsolute); it != std::rend(_toAbsolute); ++it)
        {
            appendToPath(*it);
        }
    }

    std::string result = relativePath.str();
    if (result.empty())
    {
        result = '.';
    }
    else
    {
        result.pop_back(); // remove trailing '/'
    }
    return result;
}

/// @endcond PRIVATE
