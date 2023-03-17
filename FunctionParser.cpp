#include "FunctionParser.h"

bool FunctionParser::IsGoodFunction(std::string funcName)
{
    if (!funcName.starts_with("?") || funcName.starts_with("??") || Contains(funcName, "TkSTLAllocatorShim")
        || Contains(funcName, "StackAllocator") || Contains(funcName, "cTkLinearHashTable"))
        return false;

    /*if (funcName.starts_with("?"))
        ReplaceFirst(funcName, "?", "");*/

    // ignore constructors
    //auto trimmedName = funcName.replace("::", ":");

    return  true;
}

bool FunctionParser::Contains(std::string funcName, std::string textToCheck)
{
    return funcName.find(textToCheck) != std::string::npos;
}

int FunctionParser::Count(std::string funcName, std::string textToGet)
{
    int count = 0;
    size_t nPos = funcName.find(textToGet, 0); // first occurrence
    while (nPos != std::string::npos)
    {
        count++;
        nPos = funcName.find(textToGet, nPos + 1);
    }

    return count;
}

void FunctionParser::Replace(std::string text, std::string textToReplace, std::string replaceWith)
{
    auto pos = text.find(textToReplace);
    while (pos != std::string::npos)
    {
        text.replace(pos, textToReplace.length(), replaceWith);
        pos = text.find(textToReplace);
    }
}

void FunctionParser::ReplaceFirst(std::string text, std::string textToReplace, std::string replaceWith)
{
    auto pos = text.find(textToReplace);
    text.replace(pos, textToReplace.length(), replaceWith);
}

std::vector<std::string> FunctionParser::Split(std::string str, char separator)
{
	std::vector <std::string> strings;

    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= str.size(); i++) {

        // If we reached the end of the word or the end of the input.
        if (str[i] == separator || i == str.size()) {
            endIndex = i;
            std::string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }

    return strings;
}


