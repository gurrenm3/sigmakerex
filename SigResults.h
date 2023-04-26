#pragma once
#include "Sig.h"

class SigResults
{
public:
	SIG outSig;
	ea_t sig_ea;
	UINT32 offset;
	SigResults();
	SigResults(SIG outSig, ea_t sig_ea, UINT32 offset, bool success);
	SigResults(SIG outSig, ea_t sig_ea, UINT32 offset, bool success, bool isXrefSig);
	bool DidSucceed();

private:
	bool success;
	bool isXrefSig;
};

