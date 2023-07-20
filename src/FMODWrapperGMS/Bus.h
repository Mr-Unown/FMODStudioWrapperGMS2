#pragma once
#include "Framework.h"

FMOD::Studio::Bus* busObject = nullptr;
Handles< FMOD::Studio::Bus* > BusHandles;

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

// Inline Function.
inline double getBusfromHandle(double handle) {
	auto temp = BusHandles.Get(handle);
	if (temp == nullptr) {
		return GM_error;
	}
	busObject = *temp;
	if (!busObject->isValid()) {
		BusHandles.Remove(handle);
		return GM_error;
	}
}

