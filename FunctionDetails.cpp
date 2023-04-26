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
