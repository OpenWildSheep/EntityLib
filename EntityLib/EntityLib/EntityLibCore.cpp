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

    std::string formatErrorPath(std::filesystem::path const&, std::filesystem::path const& _rel)
    {
        return format(R"("%s")", _rel.generic_string().c_str());
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

    static std::string makeWhatMessage(
        std::string const& msg,
        std::filesystem::path const& rootPath,
        std::filesystem::path const& relPath,
        std::error_code error)
    {
        return Ent::format(
            R"msg(%s - %s : %s)msg",
            msg.c_str(),
            Ent::convertANSIToUTF8(error.message()).c_str(),
            Ent::formatErrorPath(rootPath, relPath).c_str());
    }

    EntLibException::EntLibException(char const* _message)
        : std::runtime_error(_message)
    {
        messages.emplace_back(_message);
    }
    EntLibException::EntLibException(std::string _message)
        : std::runtime_error(_message)
    {
        messages.push_back(std::move(_message));
    }
    void EntLibException::addContextMessage(std::string _message)
    {
        messages.push_back(std::move(_message));
    }

    const char* EntLibException::what() const noexcept
    {
        static char buffer[4096] = {0};
        bool first = true;
        for (std::string const& msg : messages)
        {
            if (!first)
            {
                strcat_s(buffer, sizeof(buffer), "    - ");
            }
            strcat_s(buffer, sizeof(buffer), msg.c_str());
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
} // namespace Ent
