#include "System.h"

FMOD::Studio::System* FMODsystem = nullptr;
FMOD::System* lowLevelSystem = nullptr;
FMOD_REVERB_PROPERTIES reverbProperties = FMOD_PRESET_GENERIC;
void* extraDriverData = nullptr;



// Creates the FMOD System.
double fmod_create() {
	return FMODGMS_Util_ErrorChecker(FMOD::Studio::System::create(&FMODsystem));
}

// Initializes the FMOD System.
double fmod_init(double numberofchannels) {
	FMOD_RESULT result = FMODsystem->initialize(numberofchannels, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData);
	FMODsystem->getCoreSystem(&lowLevelSystem);
	lowLevelSystem->setReverbProperties(0, &reverbProperties);

	return FMODGMS_Util_ErrorChecker(result);
}

// Updates the FMOD System.
double fmod_update() {
	return FMODGMS_Util_ErrorChecker(FMODsystem->update());
}

// Releases the FMOD System.
double fmod_release() {
	return FMODGMS_Util_ErrorChecker(FMODsystem->release());
}

// Setting Global Parameters.
double fmod_global_setParameter(const char* parameter_name, double value, double ignoreseek) {
	return FMODGMS_Util_ErrorChecker(FMODsystem->setParameterByName(parameter_name, value, ignoreseek));
}

// Getting Global Parameters.
double fmod_global_getParameter(const char* parameter_name) {
	float value = 0.0f;
	float finalValue = 0.0f;
	FMODGMS_Util_ErrorChecker(FMODsystem->getParameterByName(parameter_name, &value, &finalValue));
	//double finalValue = finalValue;
	return finalValue;
}