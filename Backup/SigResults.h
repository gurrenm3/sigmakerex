#pragma once
#include <basetsd.h>
#include <idp.hpp>
#include "SigMaker.h"

class SigResults
{
public:
	SIG outSig;
	ea_t sig_ea;
	UINT32 offset;
	SigResults(SIG outSig, ea_t sig_ea, UINT32 offset, bool success);
	bool DidSucceed();

private:
	bool success;

};

