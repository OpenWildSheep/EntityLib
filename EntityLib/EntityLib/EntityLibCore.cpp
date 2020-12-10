#include "include/EntityLibCore.h"

#pragma warning(push, 0)
#include <windows.h>
#pragma warning(pop)

namespace Ent
{
    void fprintfImpl(FILE* file, char const* message)
    {
        fprintf(file, message);
        if (::IsDebuggerPresent())
        {
            ::OutputDebugStringA(message);
        }
    }

} // namespace Ent
