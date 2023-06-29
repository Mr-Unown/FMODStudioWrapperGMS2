#include <stdio.h>
#include <iostream>
#include <vector>

#include "pch.h"
#include "handler.h"
#include "framework.h"
#include "GMSDefinition.h"


void *extraDriverData = nullptr;
FMOD_RESULT result;



// Helper functions: 

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

FMOD::Studio::System* FMODsystem = nullptr;
FMOD::System* lowLevelSystem = nullptr;
FMOD_REVERB_PROPERTIES reverbProperties = FMOD_PRESET_GENERIC; // TO DO: Add customization here.

FMOD::Studio::Bank* bankObject = nullptr;
Handles< FMOD::Studio::Bank* > BankHandles;

FMOD::Studio::Bus* busObject = nullptr;
Handles< FMOD::Studio::Bus* > BusHandles;

FMOD::Studio::EventDescription* eventDescription = nullptr;
FMOD::Studio::EventInstance* eventInstance = nullptr;
Handles< FMOD::Studio::EventInstance* > EventInstHandles;
FMOD_STUDIO_PLAYBACK_STATE playbackState;

FMOD_3D_ATTRIBUTES listenerAttributes{
	{ 0.0f, 0.0f, 0.0f }, //position
	{ 0.0f, 0.0f, 0.0f }, //velocity
	{ 0.0f, 0.0f, 1.0f }, //forward
	{ 0.0f, 1.0f, 0.0f }  //up
};
// Inline Functions.
inline double getBankfromHandle(double handle) {
	auto temp = BankHandles.Get(handle); 
	if (temp == nullptr) {
		return GM_error; 
	} 
	bankObject = *temp;
	if (!bankObject->isValid()) { 
		BankHandles.Remove(handle);
		return GM_error; 
	} 
}

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

inline double getEventInstancefromHandle(double handle) {
	auto temp = EventInstHandles.Get(handle);
	if (temp == nullptr) {
		return GM_error;
	}
	eventInstance = *temp;
	if (!eventInstance->isValid()) {
		EventInstHandles.Remove(handle);
		return GM_error;
	}
}


#pragma region System Functions.

// Creates the FMOD System.
GM_FUNC double fmod_create() {
	result = FMOD::Studio::System::create(&FMODsystem);
	return FMODGMS_Util_ErrorChecker();
}

// Initializes the FMOD System.
GM_FUNC double fmod_init(double numberofchannels) {
	result = FMODsystem->initialize(numberofchannels, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData);
	FMODsystem->getCoreSystem(&lowLevelSystem);
	lowLevelSystem->setReverbProperties(0, &reverbProperties);

	return FMODGMS_Util_ErrorChecker();
}

// Updates the FMOD System.
GM_FUNC double fmod_update() {
	result = FMODsystem->update();
	return FMODGMS_Util_ErrorChecker();
}

// TODO: Add fmod_cleanup() using for each

// Releases the FMOD System.
GM_FUNC double fmod_release() {
	result = FMODsystem->release();
	return FMODGMS_Util_ErrorChecker();
}

#pragma endregion

#pragma region Bank Functions.


// Loads an FMOD Bank file.
GM_FUNC double fmod_loadBank(const char* filename) { 
	result = FMODsystem->loadBankFile(filename, FMOD_STUDIO_LOAD_BANK_NORMAL, &bankObject);
	FMODGMS_Util_ErrorChecker();
	return BankHandles.Add(bankObject);
}

// Loads FMOD Bank file Sample Data.
GM_FUNC double fmod_bank_loadSampleData(double handle) {
	getBankfromHandle(handle);
	result = bankObject->loadSampleData();
	return FMODGMS_Util_ErrorChecker();
}

// Setting Global Parameters.
GM_FUNC double fmod_global_setParameter(const char* parameter_name, double value, double ignoreseek = 0) {
	result = FMODsystem->setParameterByName(parameter_name, value, ignoreseek);
	return FMODGMS_Util_ErrorChecker();
}

// Getting Global Parameters.
GM_FUNC double fmod_global_getParameter(const char* parameter_name) {
	float value = 0.0f;
	float finalValue = 0.0f;
	result = FMODsystem->getParameterByName(parameter_name, &value, &finalValue);
	FMODGMS_Util_ErrorChecker();
	//double finalValue = finalValue;
	return finalValue;
}
#pragma endregion

#pragma region Bus Functions.


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
#pragma endregion

#pragma region Event Functions.

// Creates an Event Instance.
GM_FUNC double fmod_createEventInstance(const char* path) {
	FMODsystem->getEvent(path, &eventDescription);
	result = eventDescription->createInstance(&eventInstance);
	FMODGMS_Util_ErrorChecker();
	return EventInstHandles.Add(eventInstance);
}

// Getting Event Length.
GM_FUNC double fmod_getEventLength(const char* path) {
	int event_length = 0;
	FMODsystem->getEvent(path, &eventDescription);
	eventDescription->getLength(&event_length);
	return event_length;
}

// Starts an Event Instance.
GM_FUNC double fmod_event_play(double handle) {
	getEventInstancefromHandle(handle);
	result = eventInstance->start();
	return FMODGMS_Util_ErrorChecker();
}

// Sets pause state of an Event Instance.
GM_FUNC double fmod_event_setPause(double handle, double paused) {
	getEventInstancefromHandle(handle);
	result = eventInstance->setPaused(paused);
	return FMODGMS_Util_ErrorChecker();
}

// Gets pause state of an Event Instance.
GM_FUNC double fmod_event_getPause(double handle) {
	getEventInstancefromHandle(handle);
	bool paused = false;
	result = eventInstance->getPaused(&paused);
	FMODGMS_Util_ErrorChecker();
	return paused;
}

// Releases an Event Instance. 
GM_FUNC double fmod_event_release(double handle) {
	getEventInstancefromHandle(handle);
	eventInstance->release();
	return FMODGMS_Util_ErrorChecker();
}

// Stops an Event Instance.
GM_FUNC double fmod_event_stop(double handle, double instant) {
	getEventInstancefromHandle(handle);
	result = eventInstance->stop((instant >= 1) ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT);
	return FMODGMS_Util_ErrorChecker();
}

// Setting Event Instance Parameters.
GM_FUNC double fmod_event_setParameter(double handle, const char* parameter_name, double value, double ignoreseek = 0) {
	getEventInstancefromHandle(handle);
	result = eventInstance->setParameterByName(parameter_name, value, ignoreseek);
	return FMODGMS_Util_ErrorChecker();
}

// Getting Event Instance Parameters.
GM_FUNC double fmod_event_getParameter(double handle, const char* parameter_name) {
	float value = 0.0f;
	float finalValue = 0.0f;
	getEventInstancefromHandle(handle);
	result = eventInstance->getParameterByName(parameter_name, &value, &finalValue);
	FMODGMS_Util_ErrorChecker();
	//double finalValue = finalValue;
	return finalValue;
}

// Getting Event Instance Playback State.
GM_FUNC double fmod_event_getPlaybackState(double handle) {
	auto temp = EventInstHandles.Get(handle);
	if (temp == nullptr) {
		return FMOD_STUDIO_PLAYBACK_STOPPED;
	}
	eventInstance = *temp;
	if (!eventInstance->isValid()) {
		EventInstHandles.Remove(handle);
		return FMOD_STUDIO_PLAYBACK_STOPPED;
	}

	result = eventInstance->getPlaybackState(&playbackState);
	FMODGMS_Util_ErrorChecker();
	return playbackState;
}

// Setting Event Instance Timeline Position.
GM_FUNC double fmod_event_setTimelinePosition(double handle, double timeline_pos) {
	getEventInstancefromHandle(handle);
	result = eventInstance->setTimelinePosition(timeline_pos);
	return FMODGMS_Util_ErrorChecker();
}

// Getting Event Instance Timeline Position.
GM_FUNC double fmod_event_getTimelinePosition(double handle) {
	int timeline_pos;
	getEventInstancefromHandle(handle);
	result = eventInstance->getTimelinePosition(&timeline_pos);
	FMODGMS_Util_ErrorChecker();
	return timeline_pos;
}

// Get Event Instance Volume. 
GM_FUNC double fmod_event_getVolume(double handle) {
	getEventInstancefromHandle(handle);
	float value = 0.0f;
	float finalValue = 0.0f;
	result = eventInstance->getVolume(&value, &finalValue);
	FMODGMS_Util_ErrorChecker();
	//double finalValue = finalValue;
	return finalValue;
}

// Set Event Instance Volume. 
GM_FUNC double fmod_event_setVolume(double handle, double value) {
	getEventInstancefromHandle(handle);
	result = eventInstance->setVolume(value);
	return FMODGMS_Util_ErrorChecker();
}

// Get Event Instance Pitch. 
GM_FUNC double fmod_event_getPitch(double handle) {
	getEventInstancefromHandle(handle);
	float value = 0.0f;
	float finalValue = 0.0f;
	result = eventInstance->getPitch(&value, &finalValue);
	FMODGMS_Util_ErrorChecker();
	//double finalValue = finalValue;
	return finalValue;
}

// Set Event Instance Pitch. 
GM_FUNC double fmod_event_setPitch(double handle, double value) {
	getEventInstancefromHandle(handle);
	result = eventInstance->setPitch(value);
	return FMODGMS_Util_ErrorChecker();
}

// Get Event Instance Reverb. 
GM_FUNC double fmod_event_getReverb(double handle/*, double index*/) {
	getEventInstancefromHandle(handle);
	float value = 0.0f;
	result = eventInstance->getReverbLevel(/*index*/ 0, &value);
	FMODGMS_Util_ErrorChecker();
	return value;
}

// Set Event Instance Reverb. 
GM_FUNC double fmod_event_setReverb(double handle, /*double index,*/ double value) {
	getEventInstancefromHandle(handle);
	result = eventInstance->setReverbLevel(/*index*/ 0, value);
	return FMODGMS_Util_ErrorChecker();
}
#pragma endregion

#pragma region 3D Audio Functions.


// Set audio listener position.
GM_FUNC double fmod_listener_setPosition(double listener, double x, double y, double z = 0) {
	listenerAttributes.position = FMOD_VECTOR{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) };
	result = FMODsystem->setListenerAttributes(listener, &listenerAttributes, nullptr);
	return FMODGMS_Util_ErrorChecker();
}

// Get audio listener position.
GM_FUNC double fmod_listener_getPosition(double listener) { // unfinished.
	/*
	FMOD_3D_ATTRIBUTES tempListenerAttributes{
		{ 0.0f, 0.0f, 0.0f }, //position
		{ 0.0f, 0.0f, 0.0f }, //velocity
		{ 0.0f, 0.0f, 1.0f }, //forward
		{ 0.0f, 1.0f, 0.0f }  //up
	};
	result = FMODsystem->getListenerAttributes(listener, &tempListenerAttributes, nullptr);*/
	return GM_error;
}

// Set Event Instance 3D attributes.
GM_FUNC double fmod_event_set3DPosition(double handle, double x, double y, double z) {
	FMOD_3D_ATTRIBUTES tempListenerAttributes{
		{ 0.0f, 0.0f, 0.0f }, //position
		{ 0.0f, 0.0f, 0.0f }, //velocity
		{ 0.0f, 0.0f, 1.0f }, //forward
		{ 0.0f, 1.0f, 0.0f }  //up
	};
	tempListenerAttributes.position = FMOD_VECTOR{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) };
	getEventInstancefromHandle(handle);
	result = eventInstance->set3DAttributes(&tempListenerAttributes);
	return FMODGMS_Util_ErrorChecker();
}

#pragma endregion


