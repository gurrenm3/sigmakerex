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

bool SigResults::DidSucceed()
{
	return this->success;
}
