#include "include/EntityLib/EntityLibCore.h"

#include <system_error>

#pragma warning(push, 0)
#include <windows.h>
#pragma warning(pop)

namespace Ent
{
    LogicErrorPolicy s_LogicErrorPolicy = LogicErrorPolicy::Terminate;

    void fprintfImpl(FILE* file, char const* message)
    {
        fprintf(file, message);
        if (IsDebuggerPresent() != 0)
        {
            OutputDebugStringA(message);
        }
    }

    char const* formatPath(
        [[maybe_unused]] std::filesystem::path const& _basePath, std::filesystem::path const& _rel)
    {
        thread_local static char buffer[2048];
        sprintf_s(buffer, sizeof(buffer), R"("%s")", _rel.generic_string().c_str());
        return buffer;
    }

    std::string convertANSIToUTF8(std::string const& _message)
    {
        // CP_ACP is the system default Windows ANSI code page.
        // ANSI to utf16
        int convertResult = MultiByteToWideChar(
            CP_ACP, 0, _message.c_str(), static_cast<int>(_message.size()), nullptr, 0);
        std::wstring wide;
        wide.resize(static_cast<size_t>(convertResult));
        MultiByteToWideChar(
            CP_ACP,
            0,
            _message.c_str(),
            static_cast<int>(_message.size()),
            &wide[0],
            static_cast<int>(wide.size()));
        // utf16 to utf8
        convertResult = WideCharToMultiByte(
            CP_UTF8, 0, wide.c_str(), static_cast<int>(wide.size()), nullptr, 0, nullptr, nullptr);
        std::string result;
        result.resize(static_cast<size_t>(convertResult));
        WideCharToMultiByte(
            CP_UTF8,
            0,
            wide.c_str(),
            static_cast<int>(wide.size()),
            &result[0],
            static_cast<int>(result.size()),
            nullptr,
            nullptr);
        result.resize(static_cast<size_t>(convertResult));
        return result;
    }

    static char const* makeWhatMessage(
        std::string const& _msg,
        std::filesystem::path const& _rootPath,
        std::filesystem::path const& _relPath,
        std::error_code _error)
    {
        static constexpr auto InitBuffSize = 4096;
        thread_local static char buffer[InitBuffSize] = {0};
        sprintf_s(
            buffer,
            InitBuffSize,
            R"msg(%s - %s : %s)msg",
            _msg.c_str(),
            convertANSIToUTF8(_error.message()).c_str(),
            formatPath(_rootPath, _relPath));
        return buffer;
    }

    Exception::Exception(char const* _message)
        : std::runtime_error(_message)
    {
    }

    FileSystemError::FileSystemError(
        std::string const& _msg,
        std::filesystem::path const& _rootPath,
        std::filesystem::path const& _relPath,
        std::error_code _error)
        : ContextException(makeWhatMessage(_msg, _rootPath, _relPath, _error))
    {
    }
    FileSystemError::FileSystemError(
        std::string const& _msg,
        std::filesystem::path const& _rootPath,
        std::filesystem::path const& _relPath)
        : FileSystemError(
            _msg, _rootPath, _relPath, std::make_error_code(static_cast<std::errc>(errno)))
    {
    }

    BadType::BadType(char const* _message)
        : ContextException(_message == nullptr ? "Bad node type" : _message)
    {
    }

    BadArrayType::BadArrayType(char const* _message)
        : ContextException(_message == nullptr ? "Bad array type" : _message)
    {
    }

    MissingMetadata::MissingMetadata(char const* _schemaName)
        : ContextException("Metadata missing : %s", _schemaName)
    {
    }

    BreakSchemaRules::BreakSchemaRules(char const* _message)
        : ContextException(_message)
    {
    }

    BadUnionType::BadUnionType(char const* _type)
        : BreakSchemaRules(staticFormat("Bad union type : %s", _type))
    {
    }

    IllFormedSchema::IllFormedSchema(char const* _message)
        : ContextException("Ill-formed schema : %s", _message)
    {
    }

    InvalidJsonData::InvalidJsonData(char const* _message)
        : ContextException(_message)
    {
    }

    /// @cond PRIVATE
} // namespace Ent
