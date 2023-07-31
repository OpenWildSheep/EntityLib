#include "include/EntityLib/EntityLibCore.h"

#include <system_error>

#if defined(_MSC_VER)
#pragma warning(push, 0)
#include <windows.h>
#pragma warning(pop)
#endif

namespace Ent
{
    LogicErrorPolicy s_LogicErrorPolicy = LogicErrorPolicy::Terminate;

    void fprintfImpl(FILE* file, char const* message)
    {
        fprintf(file, message);
#if defined(_MSC_VER)
        if (IsDebuggerPresent() != 0)
        {
            OutputDebugStringA(message);
        }
#endif
    }

    char const* formatPath(
        [[maybe_unused]] std::filesystem::path const& _basePath, std::filesystem::path const& _rel)
    {
        thread_local static char buffer[2048];
        snprintf(buffer, sizeof(buffer), R"("%s")", _rel.generic_string().c_str());
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
