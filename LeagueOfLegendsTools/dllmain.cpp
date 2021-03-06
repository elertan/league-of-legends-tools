// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "Program.h"

DWORD WINAPI main_thread(LPVOID lp_thread_parameter) {
	const auto h_module = (HMODULE)lp_thread_parameter;

	Program p;
	p.main();

	// Keep library in memory
	while (true) {
		Sleep(1000);
	}
	FreeLibraryAndExitThread(h_module, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)main_thread, hModule, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

