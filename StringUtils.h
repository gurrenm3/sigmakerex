#pragma once
#include <pro.h>
#include <string>
#include <vector>

/**
 * \brief Utility methods for handling strings.
 */
class StringUtils
{
public:
	/**
	 * \brief Returns whether or not this string contains some text.
	 * \param str String to search.
	 * \param textToCheck Text to search for.
	 * \return True if text was found, otherwise false.
	 */
	static bool contains(std::string str, std::string textToCheck);

	/**
	 * \brief Returns whether or not this string contains some text.
	 * \param str String to search.
	 * \param textToCheck Text to search for.
	 * \return True if text was found, otherwise false.
	 */
	static bool q_contains(qstring str, std::string textToCheck);

	/**
	 * \brief Returns the number of times the search text occurs within a string.
	 * \param str String to search.
	 * \param textToGet Text to get count of.
	 * \return The number of times a string occurs within another string.
	 */
	static int count(std::string str, std::string textToGet);

	/**
	 * \brief Returns the number of times the search text occurs within a string.
	 * \param str String to search.
	 * \param textToGet Text to get count of.
	 * \return The number of times a string occurs within another string.
	 */
	static int q_count(qstring str, std::string textToGet);

	/**
	 * \brief Replace every occurrence of a string that is found within another string.
	 * \param str The string to replace inside of.
	 * \param textToReplace The text to actually replace.
	 * \param replaceWith The text to use instead.
	 */
	static void replace(std::string str, std::string textToReplace, std::string replaceWith);

	/**
	 * \brief Replace the first occurrence of a string that is found within another string.
	 * \param str The string to replace inside of.
	 * \param textToReplace The text to actually replace.
	 * \param replaceWith The text to use instead.
	 */
	static void replace_first(std::string str, std::string textToReplace, std::string replaceWith);

	/**
	 * \brief Split a string by a delimiter.
	 * \param str String to split.
	 * \param separator Character to separate by.
	 * \return A vector containing each part of the string, separated by the delimiter.
	 */
	static std::vector<std::string> split(std::string str, char separator);
};

