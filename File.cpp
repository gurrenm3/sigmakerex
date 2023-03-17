#include "File.h"

#include <filesystem>
#include <sstream>

File::File(std::string filePath, bool deleteExisting)
{
	this->filePath = filePath;
	if (deleteExisting && Exists())
		Delete();
}

File::~File()
{
	inFile.close();
	outFile.close();
}

void File::Open()
{
	if (outFile.is_open())
		return;

	inFile.close();
	outFile.open(filePath);

	if (!Exists())
		return;

	std::string fileText = Read();
	if (fileText.length() == 0)
		return;

	outFile << fileText;
}

std::string File::Read()
{
	outFile.close();

	std::stringstream ss;
	inFile.open(filePath);
	inFile >> ss.rdbuf();
	inFile.close();

	outFile.open(filePath);
	return ss.str();	
}

bool File::Exists()
{
	return std::filesystem::exists(filePath);
}

void File::Delete()
{
	std::filesystem::remove(filePath);
}

void File::Write(std::string text)
{
	outFile << text;
}

void File::WriteLine(std::string line)
{
	Write(line);
	Write("\n");
}