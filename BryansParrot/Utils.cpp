#include "Utils.h"

#include <sstream>
#include <iostream>
#include <algorithm>

vector<string> Utils::tokenize(string str)
{
	stringstream stream(str);

	vector<string> tokens;
	string tok;

	while (stream >> tok)
	{
		tokens.push_back(tok);
	}

	return tokens;
}

string Utils::inputValidator()
{
	char userinput[256];

	cin.getline(userinput, 256);

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	string inputStr(userinput);
	transform(inputStr.begin(), inputStr.end(), inputStr.begin(), tolower);

	return inputStr;
}

bool Utils::equalsCI(string a, string b)
{
	transform(a.begin(), a.end(), a.begin(), tolower);
	transform(b.begin(), b.end(), b.begin(), tolower);
	return a == b;
}

string Utils::strToLower(string str)
{
	transform(str.begin(), str.end(), str.begin(), tolower);
	return str;
}

bool Utils::isNumber(const string& str)
{
	for (char const& c : str)
	{
		if (!isdigit(c))
			return false;
	}

	return true;
}

bool Utils::chanceTest(float chance)
{
	int testNum = rand() % 1000;
	return testNum <= chance * 1000;
}

int Utils::randInt(int min, int max)
{
	return rand() % (max - min + 1) + min;
}
