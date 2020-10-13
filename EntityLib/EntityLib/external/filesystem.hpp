#pragma once

#if defined(_MSC_VER)
#define COMPILER_VERSION _MSVC_LANG
#else
#define COMPILER_VERSION __cplusplus
#endif

#include <filesystem>

#if COMPILER_VERSION < 201499L
namespace std
{
    using namespace experimental;
} // namespace std
#endif

#undef COMPILER_VERSION
