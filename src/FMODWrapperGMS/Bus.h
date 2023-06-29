#pragma once

#include "Framework.h"

extern Handles<FMOD::Studio::Bus*> busHandles;

inline FMOD::Studio::Bus* getBusfromHandle(double handle) {
	auto pointer = busHandles.Get(handle);

	if (pointer == nullptr)
		return nullptr;

	if (!(*pointer)->isValid())
	{
		busHandles.Remove(handle);
		return nullptr;
	}
	return *pointer;
}

// Get Bus Object.
GM_FUNC double fmod_getBus(const char* path);

// Get Bus Volume. 
GM_FUNC double fmod_bus_getVolume(double handle);

// Set Bus Volume. 
GM_FUNC double fmod_bus_setVolume(double handle, double value);

// Get Bus Mute Status. 
GM_FUNC double fmod_bus_getMute(double handle);

// Set Bus Mute Status. 
GM_FUNC double fmod_bus_setMute(double handle, double value);