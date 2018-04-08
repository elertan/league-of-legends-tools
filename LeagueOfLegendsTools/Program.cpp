#include "stdafx.h"
#include "Program.h"
#include <stdio.h>
#include "CLIArgParser.h"

// Global reference to the program instance
Program* gThis;

Program::Program()
{
}

Program::~Program()
{
}

// Servers as MITM for league's packet sending
void WSASendToDetourFn(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, const sockaddr * lpTo, int iToLen, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
}

void Program::main()
{
	gThis = this;

	// Allocate console and set cout and cin to use the console as out/input
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);

	CLIArgParser parser;
	const auto args = parser.parse(GetCommandLineA());
	cout << "Using command line arguments:" << endl;
	for (auto line : args) {
		cout << line << endl;
	}
	const auto game_id = parser.getOption(args, "-GameID");
	cout << "Game ID: " << game_id << endl;

	this->_hookManager.hook_WSASendTo(WSASendToDetourFn);
}