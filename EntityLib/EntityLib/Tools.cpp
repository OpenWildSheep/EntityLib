#include "Tools.h"

#include <fstream>
#include <sstream>
#include <ciso646>

#include "include/EntityLibCore.h"

using namespace nlohmann;

/// @cond PRIVATE

json loadJsonFile(std::filesystem::path const& path)
try
{
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (not file.is_open())
    {
        throw std::runtime_error("Can't open file for read: " + path.u8string());
    }
    auto const length = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> data((size_t(length)));
    file.read(data.data(), length);
    json doc = json::parse(
        data,
        nullptr, // Parser callback
        true, // allow_exceptions
        true // ignore_comments
    );
    return doc;
}
catch (...)
{
    ENTLIB_LOG_ERROR("parsing file %ls", path.c_str());
    throw;
}

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

std::vector<std::string> Ent::splitString(const std::string& _str, char _delimiter, bool _keepEmptyToken)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(_str);
    while (std::getline(tokenStream, token, _delimiter))
    {
        if (_keepEmptyToken or not token.empty())
        {
            tokens.push_back(token);
        }
    }
    return tokens;
}

std::string Ent::computeRelativePath(
    std::vector<std::string> _fromAbsolute, // NOLINT(performance-unnecessary-value-param)
    std::vector<std::string> _toAbsolute,
    bool _leavesAreLast)
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
