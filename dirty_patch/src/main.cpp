#include "pch.h"
#include "rl_pc.h"
#include "hook.h"
using namespace rage;

void* g_GetProcAddress{};
rlPc* g_rlPc{};

void create_console()
{
	if (!AttachConsole(GetCurrentProcessId()))
		AllocConsole();
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
}

void destroy_console()
{
	fclose(stdout);
	FreeConsole();
}

void read_config()
{
	std::ifstream file{ "socialclub_config.txt" };
	g_dll_path = { (std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>() };
	if (g_dll_path.empty())
	{
		std::cout << "No socialclub_config.txt!" << std::endl;
		g_no_fancy_shutdown = true;
		g_running = false;
	}
	file.close();
}

void scan_pointers()
{
	g_rlPc = scan("48 8D 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 48 8B 10 FF 92").add(3).rip().as<decltype(g_rlPc)>();
}

FARPROC GetProcAddressHk(HMODULE hModule, LPCSTR lpProcName)
{
	if (lpProcName == (LPCSTR)1)
	{
		scan_pointers();
		read_config();
		if (g_running)
		{
			g_rlPc->m_hRgscDll = GetModuleHandleA("socialclub.dll");
			if (g_rlPc->m_hRgscDll)
			{
				FreeLibrary(g_rlPc->m_hRgscDll);
			}
			std::cout << "Freed existing socialclub.dll" << std::endl;
			g_rlPc->m_hRgscDll = LoadLibraryExA(g_dll_path.data(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
			std::cout << "Loaded custom socialclub.dll at " << HEX(reinterpret_cast<u64>(g_rlPc->m_hRgscDll)) << std::endl;
			HMODULE mod{ GetModuleHandleA("socialclub.dll") };
			if (!mod)
			{
				std::cout << "Failed to load our custom module, likely due to it not existing." << std::endl;
				std::cout << "Loading dll supplied with GTA5.exe" << std::endl;
				g_rlPc->m_hRgscDll = LoadLibraryA("socialclub.dll");
			}
			else
			{
				char module_path[MAX_PATH]{};
				if (GetModuleFileNameA(mod, module_path, MAX_PATH) > 0)
				{
					if (!g_dll_path.compare(module_path))
					{
						std::cout << "Successfully loaded our custom socialclub.dll!" << std::endl;
					}
				}
			}
			std::cout << "Telling GetProcAddress to use it..." << std::endl;
			hModule = g_rlPc->m_hRgscDll;
		}
		FARPROC result = hk::call<FARPROC>(g_GetProcAddress, hModule, lpProcName);
		g_running = false;
		return result;
	}
	return hk::call<FARPROC>(g_GetProcAddress, hModule, lpProcName);
}

void do_fancy_shutdown(u8 time)
{
	std::cout << "Unloading in " << time << " seconds..." << std::endl;
	for (u8 i{ time }; i; --i)
	{
		std::cout << "Unloading in " << i << " seconds..." << std::endl;
		std::this_thread::sleep_for(1s);
	}
}

DWORD WINAPI routine(void* hmod)
{
	g_was_injected_early = !hmodule("socialclub.dll").exists();
	if (g_was_injected_early)
	{
		SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
		std::this_thread::sleep_for(1000ms);
	}
	g_GetProcAddress = &GetProcAddress;
	hk::create(g_GetProcAddress, GetProcAddressHk);
	std::this_thread::sleep_for(2000ms);
	create_console();
	std::cout << "Created console, applying patches..." << std::endl;
	while (g_running)
	{
		std::this_thread::sleep_for(100ms);
	}
	if (!g_no_fancy_shutdown)
	{
		std::cout << "Done! ";
		do_fancy_shutdown(10);
	}
	hk::destroy(g_GetProcAddress);
	destroy_console();
	FreeLibraryAndExitThread(HMODULE(hmod), 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hmod, DWORD  reason, LPVOID)
{
	switch (reason)
	{
		case DLL_PROCESS_ATTACH:
		{
			CreateThread(nullptr, NULL, &routine, hmod, NULL, nullptr);
		} break;
		case DLL_PROCESS_DETACH:
		{
			g_running = false;
		} break;
	}
	return TRUE;
}