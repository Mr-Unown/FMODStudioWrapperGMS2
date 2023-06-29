#pragma once

#include "Framework.h"

extern PointerHandleList<FMOD::Studio::Bus> BusHandleList;

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