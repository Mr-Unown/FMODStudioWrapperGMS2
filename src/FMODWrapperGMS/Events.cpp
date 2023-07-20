#include "System.h"
#include "Events.h"

// Creates an Event Instance.
double fmod_createEventInstance(const char* path) {
	FMODsystem->getEvent(path, &eventDescription);
	result = eventDescription->createInstance(&eventInstance);
	FMODGMS_Util_ErrorChecker();
	return EventInstHandles.Add(eventInstance);
}

// Getting Event Length.
double fmod_getEventLength(const char* path) {
	int event_length = 0;
	FMODsystem->getEvent(path, &eventDescription);
	eventDescription->getLength(&event_length);
	return event_length;
}

// Starts an Event Instance.
double fmod_event_play(double handle) {
	getEventInstancefromHandle(handle);
	result = eventInstance->start();
	return FMODGMS_Util_ErrorChecker();
}

// Sets pause state of an Event Instance.
double fmod_event_setPause(double handle, double paused) {
	getEventInstancefromHandle(handle);
	result = eventInstance->setPaused(paused);
	return FMODGMS_Util_ErrorChecker();
}

// Gets pause state of an Event Instance.
double fmod_event_getPause(double handle) {
	getEventInstancefromHandle(handle);
	bool paused = false;
	result = eventInstance->getPaused(&paused);
	FMODGMS_Util_ErrorChecker();
	return paused;
}

// Releases an Event Instance. 
double fmod_event_release(double handle) {
	getEventInstancefromHandle(handle);
	eventInstance->release();
	return FMODGMS_Util_ErrorChecker();
}

// Stops an Event Instance.
double fmod_event_stop(double handle, double instant) {
	getEventInstancefromHandle(handle);
	result = eventInstance->stop((instant >= 1) ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT);
	return FMODGMS_Util_ErrorChecker();
}

// Setting Event Instance Parameters.
double fmod_event_setParameter(double handle, const char* parameter_name, double value, double ignoreseek = 0) {
	getEventInstancefromHandle(handle);
	result = eventInstance->setParameterByName(parameter_name, value, ignoreseek);
	return FMODGMS_Util_ErrorChecker();
}

// Getting Event Instance Parameters.
double fmod_event_getParameter(double handle, const char* parameter_name) {
	float value = 0.0f;
	float finalValue = 0.0f;
	getEventInstancefromHandle(handle);
	result = eventInstance->getParameterByName(parameter_name, &value, &finalValue);
	FMODGMS_Util_ErrorChecker();
	//double finalValue = finalValue;
	return finalValue;
}

// Getting Event Instance Playback State.
double fmod_event_getPlaybackState(double handle) {
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
double fmod_event_setTimelinePosition(double handle, double timeline_pos) {
	getEventInstancefromHandle(handle);
	result = eventInstance->setTimelinePosition(timeline_pos);
	return FMODGMS_Util_ErrorChecker();
}

// Getting Event Instance Timeline Position.
double fmod_event_getTimelinePosition(double handle) {
	int timeline_pos;
	getEventInstancefromHandle(handle);
	result = eventInstance->getTimelinePosition(&timeline_pos);
	FMODGMS_Util_ErrorChecker();
	return timeline_pos;
}

// Get Event Instance Volume. 
double fmod_event_getVolume(double handle) {
	getEventInstancefromHandle(handle);
	float value = 0.0f;
	float finalValue = 0.0f;
	result = eventInstance->getVolume(&value, &finalValue);
	FMODGMS_Util_ErrorChecker();
	//double finalValue = finalValue;
	return finalValue;
}

// Set Event Instance Volume. 
double fmod_event_setVolume(double handle, double value) {
	getEventInstancefromHandle(handle);
	result = eventInstance->setVolume(value);
	return FMODGMS_Util_ErrorChecker();
}

// Get Event Instance Pitch. 
double fmod_event_getPitch(double handle) {
	getEventInstancefromHandle(handle);
	float value = 0.0f;
	float finalValue = 0.0f;
	result = eventInstance->getPitch(&value, &finalValue);
	FMODGMS_Util_ErrorChecker();
	//double finalValue = finalValue;
	return finalValue;
}

// Set Event Instance Pitch. 
double fmod_event_setPitch(double handle, double value) {
	getEventInstancefromHandle(handle);
	result = eventInstance->setPitch(value);
	return FMODGMS_Util_ErrorChecker();
}

// Get Event Instance Reverb. 
double fmod_event_getReverb(double handle/*, double index*/) {
	getEventInstancefromHandle(handle);
	float value = 0.0f;
	result = eventInstance->getReverbLevel(/*index*/ 0, &value);
	FMODGMS_Util_ErrorChecker();
	return value;
}

// Set Event Instance Reverb. 
double fmod_event_setReverb(double handle, /*double index,*/ double value) {
	getEventInstancefromHandle(handle);
	result = eventInstance->setReverbLevel(/*index*/ 0, value);
	return FMODGMS_Util_ErrorChecker();
}

// Sets pause state of all Event Instances.
double fmod_event_setPause_all(double paused) {

}

// Releases all Event Instances. 
double fmod_event_release_all() {

}

// Stops all Event Instances.
double fmod_event_stop_all(double instant) {

}