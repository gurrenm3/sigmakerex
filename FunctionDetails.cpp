#include "FunctionDetails.h"

FunctionDetails::FunctionDetails()
{
}

FunctionDetails::FunctionDetails(std::string name, std::string sig, bool isXrefSig)
{
	this->functionName = name;
	this->functionSig = sig;
	this->isXrefSig = isXrefSig;
}

FunctionDetails::FunctionDetails(std::string name, std::string sig, bool isXrefSig, bool isCtorDtor)
{
	this->functionName = name;
	this->functionSig = sig;
	this->isXrefSig = isXrefSig;
	this->isDestructor = isCtorDtor && StringUtils::contains(name, "~");
	this->isConstructor = isCtorDtor && !isDestructor;
}
