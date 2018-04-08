#include "stdafx.h"
#include "Program.h"
#include <stdio.h>

//HookManager Program::_hookManager;

Program::Program()
{
}

Program::~Program()
{
}

void WSASendToDetourFn(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, const sockaddr * lpTo, int iToLen, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
}

void Program::main()
{
	// Allocate console and set cout and cin to use the console as out/input
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);

	this->_hookManager.hook_WSASendTo(WSASendToDetourFn);
}