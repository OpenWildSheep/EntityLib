#pragma once

#include <stdexcept>
#include <array>
#include <string>
#include <filesystem>

#if defined(_MSC_VER)
#define COMPILER_VERSION _MSVC_LANG
#else
#define COMPILER_VERSION __cplusplus
#endif

#if COMPILER_VERSION < 201499L
namespace std
{
    using namespace experimental;
} // namespace std
#endif

#undef COMPILER_VERSION

char const* formatPath(std::filesystem::path const& _base, std::filesystem::path const& _rel);

struct ToolsException : std::runtime_error
{
    ToolsException(char const* _message = nullptr) noexcept;
};

/// An exception allowing to catch + add info + rethrow
struct ContextException : ToolsException
{
    ContextException() noexcept;
    template <typename... Args>
    ContextException(char const* _message, Args&&... _args) noexcept;
    ContextException(char const* _message) noexcept;
    ContextException(std::string const& _message) noexcept;
    void addContextMessage(std::string const& _message) noexcept;
    void addContextMessage(char const* _message) noexcept;
    template <typename... Args>
    void addContextMessage(char const* _message, Args&&... _args) noexcept;

    const char* what() const noexcept override;

private:
    static constexpr auto MaxContextLine = 10;
    std::array<size_t, MaxContextLine> m_context = {};
    std::array<char, 4096> m_rawContext = {};
    size_t m_contextSize = 0;
    size_t m_rawContextSize = 0;
};

template <typename... Args>
ContextException::ContextException(char const* message, Args&&... args) noexcept
{
    addContextMessage(message, std::forward<Args>(args)...);
}

template <typename... Args>
void ContextException::addContextMessage(char const* _message, Args&&... args) noexcept
{
    if (m_rawContext.size() == m_rawContextSize)
        return;
    auto const written = sprintf_s(
        m_rawContext.data() + m_rawContextSize,
        (m_rawContext.size() - m_rawContextSize) - 1,
        _message,
        std::forward<Args>(args)...);
    if (written != -1)
    {
        m_context[m_contextSize] = m_rawContextSize;
        ++m_contextSize;
        m_rawContextSize += written;
        m_rawContext[m_rawContextSize] = 0;
        ++m_rawContextSize;
    }
}

/// A ContextException which is wrapping an external
/// Usefull to add some context info on an exception which in not a ContextException
struct WrapperException : ContextException
{
    std::exception_ptr exptr;
    template <typename... Args>
    WrapperException(std::exception_ptr const& _exptr, char const* _message, Args&&... _args) noexcept;
};

/// Use FileSystemError rather than filesystem_error, since
///     - It will convert the message charset into utf8
///     - It will print the path as expected in Wild tools
struct FileSystemError : ContextException
{
    FileSystemError(
        std::string const& _msg,
        std::filesystem::path const& _rootPath,
        std::filesystem::path const& _relPath,
        std::error_code _error);

    /// This ctor will use the errno as error_code
    FileSystemError(
        std::string const& _msg,
        std::filesystem::path const& _rootPath,
        std::filesystem::path const& _relPath);
};

// *************************************** bodies *************************************************

inline char const* formatPath(
    std::filesystem::path const&, //_base,
    std::filesystem::path const& _rel)
{
    thread_local static char buffer[2048];
    sprintf_s(buffer, sizeof(buffer), R"("%s")", _rel.generic_string().c_str());
    return buffer;
}

inline ToolsException::ToolsException(char const* _message) noexcept
    : std::runtime_error(_message)
{
}

inline ContextException::ContextException() noexcept = default;

inline ContextException::ContextException(char const* _message) noexcept
    : ToolsException(_message)
{
    addContextMessage(_message);
}

inline ContextException::ContextException(std::string const& _message) noexcept
    : ContextException(_message.c_str())
{
}

inline void ContextException::addContextMessage(std::string const& _message) noexcept
{
    addContextMessage(_message.c_str());
}

inline void ContextException::addContextMessage(char const* message) noexcept
{
    if (strcpy_s(
            m_rawContext.data() + m_rawContextSize, m_rawContext.size() - m_rawContextSize, message)
        == 0)
    {
        m_context[m_contextSize] = m_rawContextSize;
        ++m_contextSize;
        m_rawContextSize += strlen(message) + 1;
    }
}

inline const char* ContextException::what() const noexcept
{
    static constexpr auto InitBuffSize = 4096;
    thread_local static char buffer[InitBuffSize] = {0};
    bool first = true;
    for (size_t i = 0; i < m_contextSize; ++i)
    {
        auto message = m_rawContext.data() + m_context[i];
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

template <typename... Args>
inline WrapperException::WrapperException(
    std::exception_ptr const& _exptr, char const* _message, Args&&... _args) noexcept
    : exptr(_exptr)
{
    try
    {
        std::rethrow_exception(exptr);
    }
    catch (std::exception& ex)
    {
        addContextMessage("%s : %s", typeid(ex).name(), ex.what());
    }
    catch (...)
    {
        addContextMessage("Unknown exception");
    }
    addContextMessage(_message, std::forward<Args>(_args)...);
}

extern "C"
{
    __declspec(dllimport) int MultiByteToWideChar(
        unsigned int CodePage,
        unsigned long dwFlags,
        char const* lpMultiByteStr,
        int cbMultiByte,
        wchar_t* lpWideCharStr,
        int cchWideChar);

    __declspec(dllimport) int WideCharToMultiByte(
        unsigned int CodePage,
        unsigned long dwFlags,
        wchar_t const* lpWideCharStr,
        int cchWideChar,
        char* lpMultiByteStr,
        int cbMultiByte,
        char const* lpDefaultChar,
        int* lpUsedDefaultChar);
}

inline std::string convertANSIToUTF8(std::string const& message)
{
    // CP_ACP is the system default Windows ANSI code page.
    constexpr auto AnsiCodePage = 0;
    constexpr auto Utf8CodePage = 65001;
    // ANSI to utf16
    int convertResult =
        MultiByteToWideChar(AnsiCodePage, 0, message.c_str(), (int)message.size(), nullptr, 0);
    std::wstring wide;
    wide.resize((size_t)convertResult);
    MultiByteToWideChar(
        AnsiCodePage, 0, message.c_str(), (int)message.size(), &wide[0], (int)wide.size());
    // utf16 to utf8
    convertResult = WideCharToMultiByte(
        Utf8CodePage, 0, wide.c_str(), (int)wide.size(), nullptr, 0, nullptr, nullptr);
    std::string result;
    result.resize((size_t)convertResult);
    WideCharToMultiByte(
        Utf8CodePage, 0, wide.c_str(), (int)wide.size(), &result[0], (int)result.size(), nullptr, nullptr);
    result.resize((size_t)convertResult);
    return result;
}

inline char const* makeWhatMessage(
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
        convertANSIToUTF8(error.message()).c_str(),
        formatPath(rootPath, relPath));
    return buffer;
}

inline FileSystemError::FileSystemError(
    std::string const& msg,
    std::filesystem::path const& rootPath,
    std::filesystem::path const& relPath,
    std::error_code error)
    : ContextException(makeWhatMessage(msg, rootPath, relPath, error))
{
}

inline FileSystemError::FileSystemError(
    std::string const& msg, std::filesystem::path const& rootPath, std::filesystem::path const& relPath)
    : FileSystemError(msg, rootPath, relPath, std::make_error_code(static_cast<std::errc>(errno)))
{
}
