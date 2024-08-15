#pragma once
#include <cstdint>
#include <windows.h>
#include <vector>
#include <functional>

namespace hk
{
	constexpr inline uint8_t shellcode
	#ifdef _WIN64
		// movabs rax, 0x0000000000000000
		// jmp rax
		[12]{ 0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xE0 };
#else
		// mov eax, 0x00000000
		// jmp eax
		[7]{ 0xB8, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xE0 };
#endif
	template <typename T>
	inline void virtual_protect(T address, size_t size, uint32_t protection, uint32_t& old_protection)
	{
		VirtualProtect(reinterpret_cast<void*>(address), size, protection, reinterpret_cast<DWORD*>(&old_protection));
	}
	struct hook
	{
		void* m_target{};
		void* m_detour{};
		char m_original[sizeof(shellcode)]{};
	};
	inline std::vector<hook> hooks;
	inline hook* get(void* target)
	{
		auto iter = std::ranges::find_if(hooks, [target](const hook& e) { return e.m_target == target; });
		return iter == hooks.end() ? nullptr : &*iter;
	}
	inline bool remove(void* target)
	{
		auto iter = std::ranges::find_if(hooks, [target](const hook& e) { return e.m_target == target; });
		if (iter == hooks.end())
			return false;
		hooks.erase(iter);
		return true;
	}
	inline bool add(const hook& context)
	{
		if (get(context.m_target))
			return false;
		hooks.push_back(context);
		return true;
	}
	template <typename T>
	inline bool exists(T target)
	{
		return get(reinterpret_cast<void*>(target)) != nullptr;
	}
	template <typename T>
	inline bool enable(T target)
	{
		hook* context{ get(reinterpret_cast<void*>(target)) };
		if (!context)
			return false;
		uint32_t old_prot{};
		virtual_protect(context->m_target, sizeof(shellcode), PAGE_EXECUTE_READWRITE, old_prot);
		memcpy(context->m_target, shellcode, sizeof(shellcode));
		size_t size{ sizeof(void*) == 8 ? 2 : 1 };
		memcpy(reinterpret_cast<char*>(context->m_target) + size, &context->m_detour, sizeof(void*));
		virtual_protect(context->m_target, sizeof(shellcode), old_prot, old_prot);
		return true;
	}

	template <typename T>
	inline bool disable(T target)
	{
		hook* context{ get(reinterpret_cast<void*>(target)) };
		if (!context)
			return false;
		uint32_t old_prot{};
		virtual_protect(context->m_target, sizeof(shellcode), PAGE_EXECUTE_READWRITE, old_prot);
		memcpy(context->m_target, context->m_original, sizeof(shellcode));
		virtual_protect(context->m_target, sizeof(shellcode), old_prot, old_prot);
		return true;
	}
	template <typename R, typename T, typename... A>
	inline R call(T target, A... args)
	{
		disable(target);
		if constexpr (!std::is_same_v<R, void>)
		{
			R retval = std::invoke((R(*)(A...))(target), std::forward<A>(args)...);
			enable(target);
			return retval;
		}
		std::invoke((R(*)(A...))(target), std::forward<A>(args)...);
		enable(target);
	}
	template <typename T, typename D>
	inline bool create(T target, D detour)
	{
		if (!target || !detour)
			return false;
		hook context{ reinterpret_cast<void*>(target), reinterpret_cast<void*>(detour) };
		memcpy(context.m_original, context.m_target, sizeof(shellcode));
		return add(context) && enable(target);
	}
	template <typename T>
	inline bool destroy(T target)
	{
		hook* context{ get(reinterpret_cast<void*>(target)) };
		if (!context)
			return false;
		return disable<T>(target) && remove(reinterpret_cast<void*>(target));
	}
}