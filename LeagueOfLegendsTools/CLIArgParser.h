#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CLIArgParser
{
public:
	vector<string> parse(string all_arguments);
	string getOption(vector<string> argument_lines, string option_name);
};

