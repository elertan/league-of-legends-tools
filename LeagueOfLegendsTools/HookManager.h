#pragma once
#include <Winsock2.h>

typedef void(*WSASendToDetour)(
	_In_  SOCKET                             s,
	_In_  LPWSABUF                           lpBuffers,
	_In_  DWORD                              dwBufferCount,
	_Out_ LPDWORD                            lpNumberOfBytesSent,
	_In_  DWORD                              dwFlags,
	_In_  const struct sockaddr              *lpTo,
	_In_  int                                iToLen,
	_In_  LPWSAOVERLAPPED                    lpOverlapped,
	_In_  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
class HookManager
{
public:
	HookManager();
	~HookManager();

	void hook_WSASendTo(WSASendToDetour detourFn);
};

