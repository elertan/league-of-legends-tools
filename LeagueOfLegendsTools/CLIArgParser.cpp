#include "stdafx.h"
#include "CLIArgParser.h"
#include <algorithm>

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
	auto removeLines = vector<string>();

	for (auto line : lines) {
		if (line.find('-') == string::npos) {
			removeLines.push_back(line);
			continue;
		}
		cout << "Arg line: " << line << endl;
	}

	for (auto line : removeLines) {
		const auto index = std::find(lines.begin(), lines.end(), line);
		lines.erase(index);
	}

	return args;
}

string CLIArgParser::getOption(vector<string> argument_lines, string option_name)
{
	for (auto line : argument_lines) {
		if (line.find(option_name) == string::npos) {
			continue;
		}

		const auto value_start_index = line.find('=') + 1;
		//const auto value_end_index = line.find_last_of('"');
		return line.substr(value_start_index, line.length - 1);
	}

	return string();
}
