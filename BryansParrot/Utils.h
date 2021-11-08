#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <map>

using namespace std;

/*
* --------------------------------------------------------------------------------------
* Class Scope
* --------------------------------------------------------------------------------------
* Static Utils class designed to hold utility functions that will be needed across the program
*
* --------------------------------------------------------------------------------------
* Methods
* --------------------------------------------------------------------------------------
* tokenize(string str)
*	breaks up a string into a vector of "tokens" that are separated by white space
* 
* inputValidator()
*	validates the given input from the console and returns the input in fully lowercase
* 
* equalsCI(string a, string b)
*	checks if the two given strings are case insensitively equal - if they are returns
*	true, else false
* 
* strToLower(string str)
*	returns str in full lowercase
* --------------------------------------------------------------------------------------
*/
class Utils
{
public:
	
	static vector<string> tokenize(string str);
	static string inputValidator();
	static bool equalsCI(string a, string b);
	static string strToLower(string str);
	static bool isNumber(const string& str);

private:
	Utils();
};

#endif // UTILS_H
