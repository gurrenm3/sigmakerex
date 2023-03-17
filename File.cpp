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
	Save();

	if (inFile.is_open())
		inFile.close();
	if (outFile.is_open())
		outFile.close();
}

void File::Open()
{
	if (!Exists())
	{
		if (inFile.is_open())
			inFile.close();

		outFile.open(filePath);
		return;
	}

	
	auto fileText = Read();
	if (fileText.length() == 0)
		return;

	outFile.open(filePath);
	outFile << fileText;
}

std::string File::Read()
{
	if (outFile.is_open())
		outFile.close();

	if (!inFile.is_open())
		inFile.open(filePath);


	std::stringstream ss;
	inFile >> ss.rdbuf();
	inFile.close();

	return ss.str();	
}

bool File::Exists()
{
	return std::filesystem::exists(filePath);
}

void File::Save()
{
	if (outFile.is_open())
		outFile.close();

	Open();
}


void File::Delete()
{
	std::filesystem::remove(filePath);
}

void File::Write(std::string text)
{
	if (!outFile.is_open())
		Open();

	outFile << text;
}

void File::WriteLine(std::string line)
{
	Write(line);
	Write("\n");
}