#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

using namespace std;

class Utils
{
public:
	static vector<string> tokenize(string str);
	static string inputValidator();
	static bool equalsCI(string a, string b);

private:
	Utils();
};

#endif // UTILS_H