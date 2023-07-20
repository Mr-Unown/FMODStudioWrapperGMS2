#include "System.h"

FMOD::Studio::System* FMODsystem = nullptr;
FMOD::System* lowLevelSystem = nullptr;
FMOD_REVERB_PROPERTIES reverbProperties = FMOD_PRESET_GENERIC;
void* extraDriverData = nullptr;



// Creates the FMOD System.
double fmod_create() {
	result = FMOD::Studio::System::create(&FMODsystem);
	return FMODGMS_Util_ErrorChecker();
}

// Initializes the FMOD System.
double fmod_init(double numberofchannels) {
	result = FMODsystem->initialize(numberofchannels, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData);
	FMODsystem->getCoreSystem(&lowLevelSystem);
	lowLevelSystem->setReverbProperties(0, &reverbProperties);

	return FMODGMS_Util_ErrorChecker();
}

// Updates the FMOD System.
double fmod_update() {
	result = FMODsystem->update();
	return FMODGMS_Util_ErrorChecker();
}

// Releases the FMOD System.
double fmod_release() {
	result = FMODsystem->release();
	return FMODGMS_Util_ErrorChecker();
}

// Setting Global Parameters.
double fmod_global_setParameter(const char* parameter_name, double value, double ignoreseek) {
	result = FMODsystem->setParameterByName(parameter_name, value, ignoreseek);
	return FMODGMS_Util_ErrorChecker();
}

// Getting Global Parameters.
double fmod_global_getParameter(const char* parameter_name) {
	float value = 0.0f;
	float finalValue = 0.0f;
	result = FMODsystem->getParameterByName(parameter_name, &value, &finalValue);
	FMODGMS_Util_ErrorChecker();
	//double finalValue = finalValue;
	return finalValue;
}