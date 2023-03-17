#pragma once
#include <string>
#include <vector>

class FunctionParser
{
public:
	bool IsGoodFunction(std::string funcName);
	bool Contains(std::string funcName, std::string textToCheck);
	int Count(std::string funcName, std::string textToGet);
	void Replace(std::string text, std::string textToReplace, std::string replaceWith);
	void ReplaceFirst(std::string text, std::string textToReplace, std::string replaceWith);
	std::vector<std::string> Split(std::string textToSplit, char separator);
};

