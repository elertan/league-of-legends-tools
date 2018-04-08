#include "stdafx.h"
#include "HookManager.h"

bool place_hook(void* hook_address, void* trampoline_fn, int opcode_length) {
	if (opcode_length < 5) {
		return false;
	}

	DWORD cur_protect;
	VirtualProtect(hook_address, opcode_length, PAGE_EXECUTE_READWRITE, &cur_protect);

	memset(hook_address, 0x90, opcode_length);

	DWORD rel_address = ((DWORD)trampoline_fn - (DWORD)hook_address) - 5;
	*(BYTE*)hook_address = 0xE9;
	*(DWORD*)((DWORD)hook_address + 1) = rel_address;

	DWORD _;
	VirtualProtect(hook_address, opcode_length, cur_protect, &_);

	return true;
}

HookManager::HookManager()
{
}


HookManager::~HookManager()
{
}

WSASendToDetour WSASendTo_detour_fn = nullptr;
DWORD WSASendTo_detour_fn_return_address;
void __declspec(naked) WSASendTo_hook_fn(
	_In_  SOCKET                             s,
	_In_  LPWSABUF                           lpBuffers,
	_In_  DWORD                              dwBufferCount,
	_Out_ LPDWORD                            lpNumberOfBytesSent,
	_In_  DWORD                              dwFlags,
	_In_  const struct sockaddr              *lpTo,
	_In_  int                                iToLen,
	_In_  LPWSAOVERLAPPED                    lpOverlapped,
	_In_  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutin
) {
	__asm {
		MOV edi, edi
		PUSH ebp
		MOV ebp, esp
		PUSHAD
	}
	WSASendTo_detour_fn(
		s,
		lpBuffers,
		dwBufferCount,
		lpNumberOfBytesSent,
		dwFlags,
		lpTo,
		iToLen,
		lpOverlapped,
		lpCompletionRoutin
	);
	__asm {
		POPAD
		JMP [WSASendTo_detour_fn_return_address]
	}
}

void HookManager::hook_WSASendTo(WSASendToDetour detourFn)
{
	const auto module_handle = GetModuleHandleA("ws2_32");
	const auto WSASendTo_fn_ptr = GetProcAddress(module_handle, "WSASendTo");

	WSASendTo_detour_fn = detourFn;
	WSASendTo_detour_fn_return_address = (DWORD)WSASendTo_fn_ptr + 5;
	place_hook(WSASendTo_fn_ptr, WSASendTo_hook_fn, 5);
}
