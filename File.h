#pragma once
#include <string>
#include <fstream>

/**
 * \brief A wrapper for easily writing to file.
 */
class File
{
public:
	/**
	 * \brief Create a File object.
	 * \param filePath The location of the file. It will be created if it doesn't exist.
	 * \param deleteExisting Whether or not to delete the file if it already exists.
	 */
	File(std::string filePath, bool deleteExisting = true);
	~File();

	/**
	 * \brief Open's the file and loads any existing text.
	 */
	void Open();

	/**
	 * \brief Read the text from file
	 * \return The text stored in the file if any.
	 */
	std::string Read();

	/**
	 * \brief Returns whether or not this file exists.
	 * \return Whether or not the file currently exists.
	 */
	bool Exists();

	/**
	 * \brief Deletes the file if it exists.
	 */
	void Delete();

	/**
	 * \brief Write some text to the file.
	 * \param text Text to write.
	 */
	void Write(std::string text);

	/**
	 * \brief Write some text to the file, followed by a new line.
	 * \param line Text to write.
	 */
	void WriteLine(std::string line);

private:
	std::ifstream inFile;
	std::ofstream outFile;
	std::string filePath;
};

