#pragma once

#define WIN32_EXTRA_LEAN       // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <fmod_errors.h>
#include "Handles.h"


#define GM_FUNC extern "C" __declspec (dllexport)

#define GM_true 1
#define GM_false 0
#define GM_error -1;
#define GM_noone -4;

void* extraDriverData = nullptr;
FMOD_RESULT result;

// Helper function.
// This converts FMOD Results to error message strings and returns GM_true (1.0) if 
// the Result is FMOD_OK and GM_error (-1) otherwise.
double FMODGMS_Util_ErrorChecker() {
	const char* errorMessage = FMOD_ErrorString(result);

	if (result != FMOD_OK) {
		//const char text = "FMOD error!(% d) % s\n" + errorMessage;
		std::cout << "FMOD error!(% d) % s\n" << errorMessage << std::endl;

		return GM_error;
	}
	else {
		return GM_true;
	}
}