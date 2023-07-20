#include "System.h"
#include "Bus.h"

FMOD::Studio::Bus* busObject = nullptr;
Handles< FMOD::Studio::Bus* > BusHandles;



// Get Bus Object.
GM_FUNC double fmod_getBus(const char* path) {
	FMODGMS_Util_ErrorChecker(FMODsystem->getBus(path, &busObject));
	return BusHandles.Add(busObject);
}

// Get Bus Volume. 
GM_FUNC double fmod_bus_getVolume(double handle) {
	getBusfromHandle(handle);
	float value = 0.0f;
	float finalValue = 0.0f;
	FMODGMS_Util_ErrorChecker(busObject->getVolume(&value, &finalValue));
	//double finalValue = finalValue;
	return finalValue;
}

// Set Bus Volume. 
GM_FUNC double fmod_bus_setVolume(double handle, double value) {
	getBusfromHandle(handle);
	return FMODGMS_Util_ErrorChecker(busObject->setVolume(value));
}

// Get Bus Mute Status. 
GM_FUNC double fmod_bus_getMute(double handle) {
	getBusfromHandle(handle);
	bool value = false;
	FMODGMS_Util_ErrorChecker(busObject->getMute(&value));
	return value;
}

// Set Bus Mute Status. 
GM_FUNC double fmod_bus_setMute(double handle, double value) {
	getBusfromHandle(handle);
	return FMODGMS_Util_ErrorChecker(busObject->setMute(value));
}