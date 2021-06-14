#include "include/EntityLibCore.h"

#include <system_error>

#pragma warning(push, 0)
#include <windows.h>
#pragma warning(pop)

namespace Ent
{
    void fprintfImpl(FILE* file, char const* message)
    {
        fprintf(file, message);
        if (::IsDebuggerPresent() != 0)
        {
            ::OutputDebugStringA(message);
        }
    }

    char const* formatErrorPath(std::filesystem::path const&, std::filesystem::path const& _rel)
    {
        thread_local static char buffer[2048];
        sprintf_s(buffer, sizeof(buffer), R"("%s")", _rel.generic_string().c_str());
        return buffer;
    }

    std::string convertANSIToUTF8(std::string const& message)
    {
        // CP_ACP is the system default Windows ANSI code page.
        // ANSI to utf16
        int convertResult =
            MultiByteToWideChar(CP_ACP, 0, message.c_str(), (int)message.size(), nullptr, 0);
        std::wstring wide;
        wide.resize((size_t)convertResult);
        MultiByteToWideChar(
            CP_ACP, 0, message.c_str(), (int)message.size(), &wide[0], (int)wide.size());
        // utf16 to utf8
        convertResult = WideCharToMultiByte(
            CP_UTF8, 0, wide.c_str(), (int)wide.size(), nullptr, 0, nullptr, nullptr);
        std::string result;
        result.resize((size_t)convertResult);
        WideCharToMultiByte(
            CP_UTF8, 0, wide.c_str(), (int)wide.size(), &result[0], (int)result.size(), nullptr, nullptr);
        result.resize((size_t)convertResult);
        return result;
    }

    static char const* makeWhatMessage(
        std::string const& msg,
        std::filesystem::path const& rootPath,
        std::filesystem::path const& relPath,
        std::error_code error)
    {
        static constexpr auto InitBuffSize = 4096;
        thread_local static char buffer[InitBuffSize] = {0};
        sprintf_s(
            buffer,
            InitBuffSize,
            R"msg(%s - %s : %s)msg",
            msg.c_str(),
            Ent::convertANSIToUTF8(error.message()).c_str(),
            Ent::formatErrorPath(rootPath, relPath));
        return buffer;
    }

    EntLibException::EntLibException(char const* _message) noexcept
        : std::runtime_error(_message)
    {
        addContextMessage(_message);
    }
    EntLibException::EntLibException(std::string const& _message) noexcept
        : std::runtime_error(_message)
    {
        addContextMessage(_message.c_str());
    }
    void EntLibException::addContextMessage(std::string const& _message) noexcept
    {
        addContextMessage(_message.c_str());
    }

    void EntLibException::addContextMessage(char const* message) noexcept
    {
        if (strcpy_s(rawContext.data() + rawContextSize, rawContext.size() - rawContextSize, message)
            == 0)
        {
            context[contextSize] = rawContextSize;
            ++contextSize;
            rawContextSize += strlen(message) + 1;
        }
    }

    const char* EntLibException::what() const noexcept
    {
        static constexpr auto InitBuffSize = 4096;
        thread_local static char buffer[InitBuffSize] = {0};
        bool first = true;
        for (size_t i = 0; i < contextSize; ++i)
        {
            auto message = rawContext.data() + context[i];
            if (!first)
            {
                strcat_s(buffer, sizeof(buffer), "    - ");
            }
            strcat_s(buffer, sizeof(buffer), message);
            strcat_s(buffer, sizeof(buffer), "\n");
            first = false;
        }
        return buffer;
    }

    FileSystemError::FileSystemError(
        std::string const& msg,
        std::filesystem::path const& rootPath,
        std::filesystem::path const& relPath,
        std::error_code error)
        : EntLibException(makeWhatMessage(msg, rootPath, relPath, error))
    {
    }
    FileSystemError::FileSystemError(
        std::string const& msg,
        std::filesystem::path const& rootPath,
        std::filesystem::path const& relPath)
        : FileSystemError(msg, rootPath, relPath, std::make_error_code(static_cast<std::errc>(errno)))
    {
    }

    BadType::BadType(char const* _message)
        : EntLibException(_message == nullptr ? "Bad node type" : _message)
    {
    }

    BadArrayType::BadArrayType(char const* _message)
        : EntLibException(_message == nullptr ? "Bad array type" : _message)
    {
    }

    MissingMetadata::MissingMetadata(char const* _schemaName)
        : EntLibException(staticFormat("Metadata missing : %s", _schemaName))
    {
    }

    BadUnionType::BadUnionType(char const* _type)
        : EntLibException(staticFormat("Bad union type : %s", _type))
    {
    }

    IllFormedSchema::IllFormedSchema(char const* _message)
        : EntLibException(staticFormat("Ill-formed schema : %s", _message))
    {
    }

    InvalidJsonData::InvalidJsonData(char const* _message)
        : EntLibException(_message)
    {
    }

    /// @cond PRIVATE
} // namespace Ent
