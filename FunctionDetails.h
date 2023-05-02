#pragma once
#include <string>
#include "StringUtils.h"

class FunctionDetails
{
public:
	std::string functionName;
	std::string functionSig;
	bool isXrefSig;
	bool isConstructor;
	bool isDestructor;
	FunctionDetails();
	FunctionDetails(std::string name, std::string sig, bool isXrefSig);
	FunctionDetails(std::string name, std::string sig, bool isXrefSig, bool isConstructor);
};

