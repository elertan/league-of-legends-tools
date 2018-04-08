#include "stdafx.h"
#include "CLIArgParser.h"

void split(const string& s, char delim, vector<string>& v) {
	auto i = 0;
	auto pos = s.find(delim);
	while (pos != string::npos) {
		v.push_back(s.substr(i, pos - i));
		i = ++pos;
		pos = s.find(delim, pos);

		if (pos == string::npos)
			v.push_back(s.substr(i, s.length()));
	}
}

vector<string> CLIArgParser::parse(string all_arguments)
{
	auto args = vector<string>();

	auto lines = vector<string>();
	split(all_arguments, ' ', lines);

	for (auto line : lines) {
		cout << "Arg line: " << line << endl;
	}

	return args;
}

string CLIArgParser::getOption(vector<string> argument_lines, string option_name)
{
	return string();
}
