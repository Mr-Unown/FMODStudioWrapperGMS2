#pragma once

#include "Framework.h"

extern FMOD::Studio::Bank* bankObject;
extern Handles< FMOD::Studio::Bank* > BankHandles;

// Loads an FMOD Bank file.
GM_FUNC double fmod_loadBank(const char* filename);

// Loads FMOD Bank file Sample Data.
GM_FUNC double fmod_bank_loadSampleData(double handle);

// Inline Function.
inline double getBankfromHandle(double handle) {
	auto temp = BankHandles.Get(handle); 
	if (temp == nullptr) {
		return GM_error; 
	} 
	bankObject = *temp;
	if (!bankObject->isValid()) { 
		BankHandles.Remove(handle);
		return GM_error; 
	} 
}

