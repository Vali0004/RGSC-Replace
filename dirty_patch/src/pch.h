#ifndef PCH_H
#define PCH_H

// Shortened types
using u64 = unsigned long long;
using s64 = signed long long;
using u32 = unsigned int;
using s32 = int;
using u16 = unsigned short;
using s16 = signed short;
using u8 = unsigned char;
using s8 = signed char;

// Default includes
#include "framework.h"
#include "memory.h"

// Joaat functions
inline constexpr char j_to_lower(char const c)
{
	return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}
inline consteval u32 operator ""_j(const char* str, u64)
{
	u32 hash{};

	while (*str != '\0')
	{
		hash += j_to_lower(*str);
		++str;
		hash += hash << 10;
		hash ^= hash >> 6;
	}

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return hash;
}

// Helper macros
#define HEX(v) "0x" << std::uppercase << std::hex << v
#define UNUSED_PARAM(x) x
#define rtry try
#define rcatchall catch(...)
#define rverifyall

// Variables used in a global context
inline bool g_running{ true };
inline bool g_no_fancy_shutdown{};
inline bool g_was_injected_early{};
inline std::string g_dll_path{};

#endif //PCH_H