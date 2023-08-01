#include <Windows.h>
#include <iostream>
#include <cstdio>

#include "d3d11hook.h"
#include "Menus.h"
#include "MinHook.h"
#include "Hooks.h"
#include "Game.h"

D3D11Hook MyHook;
MyGame g_Game;

DWORD WINAPI HackThread(HMODULE hModule) {

	MyHook.MyMenu = MyMenu;
	AllocConsole();
	FILE* fp = NULL;
	freopen_s(&fp, "CONOUT$", "w", stdout);

	int result = 0;

	if (!(result = MyHook.d3d11InitHook()))
	{
		printf("Result: %d\n", result);
		goto END;
	}

	if (MH_OK != (result = MH_Initialize()))
	{
		printf("[-] MH_Initialize: %d\n", result);
	}
	else
	{
		puts("[+] MH_Initialize");
	}

	if (MH_OK != (result = init_hooks()))
	{
		printf("[-] init_hooks: %d\n", result);
	}
	else
	{
		puts("[+] init_hooks;");
	}

LOOP:
	while (1) {
		if (GetAsyncKeyState(VK_END) & 1)
		{
			MyHook.bShutDown = true;
			Sleep(500);
			break;
		}

		Sleep(5);
	}

	//MyHook.d3d11UnHook();

END:
	puts("ending");
	Sleep(1000);
	fclose(fp);
	FreeConsole();

	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();

	MyHook.d3d11UnHook();

	FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hModule);

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:

		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
