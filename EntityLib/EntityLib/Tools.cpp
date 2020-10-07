#include "Tools.h"

#include <fstream>
#include <sstream>

using namespace nlohmann;

static std::tuple<std::string, int> exec(char const* command)
{
    // Open pipe to file
    FILE* pipe = _popen(command, "r");
    if (pipe == nullptr)
    {
        return { "popen failed!", -1 };
    }

    // read till end of process:
    char buffer[128];
    std::string result;
    while (feof(pipe) == 0)
    {
        // use buffer to read and add to result
        if (fgets(buffer, 128, pipe) != nullptr)
        {
            result += buffer;
        }
    }

    auto exitCode = _pclose(pipe);
    return { std::move(result), exitCode };
}

json loadJsonFile(std::filesystem::path const& _toolsDir, std::filesystem::path const& _path)
{
    // Call the mcpp preprocessor to remove all C-style comments inside the json file
    auto mcppPath = _toolsDir / "External/mcpp/mcpp.exe";
    std::stringstream ss;
    ss << mcppPath << " ";
    ss << _path << " -P -a -W 0";
    std::string data;
    int errorCode{};
    std::tie(data, errorCode) = exec(ss.str().c_str()); // NOLINT(readability-redundant-string-cstr)
    if (errorCode != 0)
    {
        throw std::runtime_error("Can't preprocess file: " + _path.u8string());
    }

    json doc = json::parse(data);
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
    std::vector<std::string> _fromAbsolute, 
    std::vector<std::string> _toAbsolute,
    bool _leavesAreLast)
{
    using PopRootFun = void(*)(std::vector<std::string>&);
    const auto popRoot = _leavesAreLast ? 
         static_cast<PopRootFun>([](std::vector<std::string>& _path)
         {
             _path.erase(_path.begin());
         }) :
         static_cast<PopRootFun>([](std::vector<std::string>& _path)
         {
             _path.pop_back();
         });
  
    using GetRootFun = std::string&(*)(std::vector<std::string>&);
    const auto getRoot = _leavesAreLast ? 
        static_cast<GetRootFun>([](
            std::vector<std::string>& _path) -> std::string& { return _path.front(); }) :
        static_cast<GetRootFun>([](
            std::vector<std::string>& _path) -> std::string& { return _path.back(); });

    // remove common ancestors
    while (not _fromAbsolute.empty() 
		and not _toAbsolute.empty() 
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
    const auto appendToPath = [&relativePath](std::string& _pathPart)
    {
        relativePath << _pathPart << '/';
    };
    if (_leavesAreLast)
    {
        for (auto it = std::begin(_toAbsolute); 
            it != std::end(_toAbsolute); ++it)
        {
            appendToPath(*it);
        }
    }
    else
    {
        for (auto it = std::rbegin(_toAbsolute); 
            it != std::rend(_toAbsolute); ++it)
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
