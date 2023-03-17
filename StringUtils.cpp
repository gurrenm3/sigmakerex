#include "StringUtils.h"

bool StringUtils::contains(std::string str, std::string textToCheck)
{
	return str.find(textToCheck) != std::string::npos;
}

bool StringUtils::q_contains(qstring str, std::string textToCheck)
{
    return str.find(textToCheck.c_str()) != std::string::npos;
}

int StringUtils::count(std::string str, std::string textToGet)
{
    int count = 0;
    size_t nPos = str.find(textToGet, 0); // first occurrence
    while (nPos != std::string::npos)
    {
        count++;
        nPos = str.find(textToGet, nPos + 1);
    }

    return count;
}

int StringUtils::q_count(qstring str, std::string textToGet)
{
    int count = 0;
    size_t nPos = str.find(textToGet.c_str(), 0); // first occurrence
    while (nPos != std::string::npos)
    {
        count++;
        nPos = str.find(textToGet.c_str(), nPos + 1);
    }

    return count;
}

void StringUtils::replace(std::string str, std::string textToReplace, std::string replaceWith)
{
    auto pos = str.find(textToReplace);
    while (pos != std::string::npos)
    {
        str.replace(pos, textToReplace.length(), replaceWith);
        pos = str.find(textToReplace);
    }
}

void StringUtils::replace_first(std::string str, std::string textToReplace, std::string replaceWith)
{
    auto pos = str.find(textToReplace);
    str.replace(pos, textToReplace.length(), replaceWith);
}

std::vector<std::string> StringUtils::split(std::string str, char separator)
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