#pragma once
#include "HookManager.h"

class Program
{
public:
	Program();
	~Program();

	void main();
private:
	HookManager _hookManager;
};

