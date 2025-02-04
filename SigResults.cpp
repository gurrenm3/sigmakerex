#include "SigResults.h"

SigResults::SigResults()
{
	this->success = false;
}

SigResults::SigResults(SIG outSig, ea_t sig_ea, UINT32 offset, bool success)
{
	this->outSig = outSig;
	this->sig_ea = sig_ea;
	this->offset = offset;
	this->success = success;
}

SigResults::SigResults(SIG outSig, ea_t sig_ea, UINT32 offset, bool success, bool isXrefSig)
{
	this->outSig = outSig;
	this->sig_ea = sig_ea;
	this->offset = offset;
	this->success = success;
	this->isXrefSig = isXrefSig;
}

bool SigResults::DidSucceed()
{
	return this->success;
}

bool SigResults::IsXRefSig()
{
	return this->isXrefSig;
}
