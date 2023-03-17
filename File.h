#pragma once
#include <string>
#include <fstream>

class File
{
public:
	File(std::string filePath, bool deleteExisting = true);
	~File();
	void Open();
	std::string Read();
	bool Exists();
	void Save();
	void Delete();
	void Write(std::string text);
	void WriteLine(std::string line);

private:
	std::ifstream inFile;
	std::ofstream outFile;
	std::string filePath;
};

