#pragma once

#include "Framework.h"

extern Handles<FMOD::Studio::Bank*> bankHandles;

inline FMOD::Studio::Bank* getBankfromHandle(double handle)
{
	auto pointer = bankHandles.Get(handle);

	if (pointer == nullptr)
		return nullptr;

	if (!(*pointer)->isValid())
	{
		bankHandles.Remove(handle);
		return nullptr;
	}

	return *pointer;
}

// Loads an FMOD Bank file.
GM_FUNC double fmod_loadBank(const char* filename);

// Loads FMOD Bank file Sample Data.
GM_FUNC double fmod_bank_loadSampleData(double handle);

// Setting Global Parameters.
GM_FUNC double fmod_global_setParameter(const char* parameterName, double value, double ignoreSeek = 0);

// Getting Global Parameters.
GM_FUNC double fmod_global_getParameter(const char* parameterName);