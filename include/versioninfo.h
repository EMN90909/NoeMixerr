#ifndef NoeMixerr_VERSION_INFO_H
#define NoeMixerr_VERSION_INFO_H

#include "NoeMixerrCommonMacros.h"
#include "noemixerrconfig.h"

#if defined(__clang__)
constexpr const char* NoeMixerr_BUILDCONF_COMPILER_VERSION = "Clang " __clang_version__;
#elif defined(__GNUC__)
constexpr const char* NoeMixerr_BUILDCONF_COMPILER_VERSION = "GCC " __VERSION__;
#elif defined(_MSC_VER)
constexpr const char* NoeMixerr_BUILDCONF_COMPILER_VERSION = "MSVC " NoeMixerr_STRINGIFY(_MSC_FULL_VER);
#else
constexpr const char* NoeMixerr_BUILDCONF_COMPILER_VERSION = "unknown compiler";
#endif

#if defined(NoeMixerr_HOST_X86)
constexpr const char* NoeMixerr_BUILDCONF_MACHINE = "i386";
#elif defined(NoeMixerr_HOST_X86_64)
constexpr const char* NoeMixerr_BUILDCONF_MACHINE = "x86_64";
#elif defined(NoeMixerr_HOST_ARM32)
constexpr const char* NoeMixerr_BUILDCONF_MACHINE = "arm32";
#elif defined(NoeMixerr_HOST_ARM64)
constexpr const char* NoeMixerr_BUILDCONF_MACHINE = "arm64";
#elif defined(NoeMixerr_HOST_RISCV32)
constexpr const char* NoeMixerr_BUILDCONF_MACHINE = "riscv32";
#elif defined(NoeMixerr_HOST_RISCV64)
constexpr const char* NoeMixerr_BUILDCONF_MACHINE = "riscv64";
#elif defined(NoeMixerr_HOST_PPC32)
constexpr const char* NoeMixerr_BUILDCONF_MACHINE = "ppc";
#elif defined(NoeMixerr_HOST_PPC64)
constexpr const char* NoeMixerr_BUILDCONF_MACHINE = "ppc64";
#else
constexpr const char* NoeMixerr_BUILDCONF_MACHINE = "unknown processor";
#endif

#if defined(NoeMixerr_BUILD_LINUX)
constexpr const char* NoeMixerr_BUILDCONF_PLATFORM = "Linux";
#elif defined(NoeMixerr_BUILD_APPLE)
constexpr const char* NoeMixerr_BUILDCONF_PLATFORM = "OS X";
#elif defined(NoeMixerr_BUILD_OPENBSD)
constexpr const char* NoeMixerr_BUILDCONF_PLATFORM = "OpenBSD";
#elif defined(NoeMixerr_BUILD_FREEBSD)
constexpr const char* NoeMixerr_BUILDCONF_PLATFORM = "FreeBSD";
#elif defined(NoeMixerr_BUILD_WIN32)
constexpr const char* NoeMixerr_BUILDCONF_PLATFORM = "win32";
#elif defined(NoeMixerr_BUILD_HAIKU)
constexpr const char* NoeMixerr_BUILDCONF_PLATFORM = "Haiku";
#elif defined(NoeMixerr_BUILD_CYGWIN)
constexpr const char* NoeMixerr_BUILDCONF_PLATFORM = "Cygwin";
#else
constexpr const char* NoeMixerr_BUILDCONF_PLATFORM = "unknown platform";
#endif

#endif // NoeMixerr_VERSION_INFO_H
