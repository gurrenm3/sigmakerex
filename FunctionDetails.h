#pragma once
#include <string>
class FunctionDetails
{
public:
	std::string functionName;
	std::string functionSig;
	bool isXrefSig;
	FunctionDetails();
	FunctionDetails(std::string name, std::string sig, bool isXrefSig);
};

