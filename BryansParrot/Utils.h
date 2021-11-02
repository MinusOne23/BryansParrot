#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <map>

using namespace std;

class Utils
{
public:

	struct ActionResult
	{
		int interaction;
		string objectName;
		string actionStr;
	};

	template<typename T>
	static ActionResult actionChecker(const map<string, T>& actionMap, const string& input, int MAX_WORDS = 1);
	
	static vector<string> tokenize(string str);
	static string inputValidator();
	static bool equalsCI(string a, string b);
	static string strToLower(string str);

private:
	Utils();
};

#endif // UTILS_H

template<typename T>
Utils::ActionResult Utils::actionChecker(const map<string, T>& actionMap, const string& input, int MAX_WORDS)
{
	ActionResult result;
	vector<string> tokens = Utils::tokenize(input);

	for (int i = 1; i < tokens.size() + 1 && i <= MAX_WORDS; i++)
	{
		string actionStr = tokens[0];

		for (int j = 1; j < i; j++)
		{
			actionStr += " " + tokens[j];
		}

		if (actionMap.find(actionStr) != actionMap.end())
		{
			result.interaction = (int)actionMap.at(actionStr);

			if (i < tokens.size())
			{
				result.objectName = tokens[i];
				for (int j = i + 1; j < tokens.size(); j++)
				{
					result.objectName += " " + tokens[j];
				}
			}

			result.actionStr = strToLower(actionStr);

			return result;
		}
	}

	result.interaction = -1;
	return result;
}
