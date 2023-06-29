#pragma once

// Original Code by Unown
// Refactor done by RadixComet
// (blame RadixComet if stuff is broken I'll fix it!)

#define WIN32_LEAN_AND_MEAN	// Exclude rarely-used stuff from Windows headers
// RadixComet: Turns out you only need VC_EXTRA_LEAN for MFC Apps, Oops!

// Windows Header Files
#include <windows.h>

// FMOD Header Files
#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <fmod_errors.h>

#include "GMSDefinition.h"
#include "Handler.h"

#include <stdio.h>
#include <iostream>
#include <vector>

// This converts FMOD Results to error message strings and returns GM_true (1.0) if 
// the Result is FMOD_OK and GM_error (-1) otherwise.
inline double FMODGMS_Util_ErrorChecker(const FMOD_RESULT& result)
{
	const char* errorMessage = FMOD_ErrorString(result);

	if (result == FMOD_OK)
		return GM_true();

	std::cout << "FMOD error!(% d) % s\n" << errorMessage << std::endl;
	return GM_error();
}