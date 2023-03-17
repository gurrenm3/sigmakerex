
// Common and shared
#pragma once
#include "Sig.h"
#include "SigResults.h"

// Minimal signature byte length
static const UINT32 MIN_SIG_SIZE = 5;


// Search.cpp
enum SSTATUS
{
	NOT_FOUND,	// Signature not found error
	UNIQUE,		// Unique, single instance found
	NOT_UNIQUE	// Not unique, more than one instance found
};
SSTATUS SearchSignature(const SIG &sig, bool showMsgs);
void SearchCleanup();

// Signature.cpp
SigResults CreateFunctionSig(func_t* pfn, bool showMsgs);
void CreateFunctionSig();
void CreateFunctionSigInBulk();
void CreateAddressSig();
void CreateAddressRangeSig();
void OutputSignature(const SIG &sig, ea_t address, UINT32 offset, bool showMsgs);
