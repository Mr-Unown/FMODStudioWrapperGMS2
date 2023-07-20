#include "System.h"
#include "Bus.h"

// Get Bus Object.
GM_FUNC double fmod_getBus(const char* path) {
	result = FMODsystem->getBus(path, &busObject);
	FMODGMS_Util_ErrorChecker();
	return BusHandles.Add(busObject);
}

// Get Bus Volume. 
GM_FUNC double fmod_bus_getVolume(double handle) {
	getBusfromHandle(handle);
	float value = 0.0f;
	float finalValue = 0.0f;
	result = busObject->getVolume(&value, &finalValue);
	FMODGMS_Util_ErrorChecker();
	//double finalValue = finalValue;
	return finalValue;
}

// Set Bus Volume. 
GM_FUNC double fmod_bus_setVolume(double handle, double value) {
	getBusfromHandle(handle);
	result = busObject->setVolume(value);
	return FMODGMS_Util_ErrorChecker();
}

// Get Bus Mute Status. 
GM_FUNC double fmod_bus_getMute(double handle) {
	getBusfromHandle(handle);
	bool value = false;
	result = busObject->getMute(&value);
	FMODGMS_Util_ErrorChecker();
	return value;
}

// Set Bus Mute Status. 
GM_FUNC double fmod_bus_setMute(double handle, double value) {
	getBusfromHandle(handle);
	result = busObject->setMute(value);
	return FMODGMS_Util_ErrorChecker();
}