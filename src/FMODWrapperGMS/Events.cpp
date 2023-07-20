#include "System.h"
#include "Events.h"

FMOD::Studio::EventDescription* eventDescription = nullptr;
FMOD::Studio::EventInstance* eventInstance = nullptr;
Handles< FMOD::Studio::EventInstance* > EventInstHandles;
FMOD_STUDIO_PLAYBACK_STATE playbackState;



// Creates an Event Instance.
double fmod_createEventInstance(const char* path) {
	FMODsystem->getEvent(path, &eventDescription);
	FMODGMS_Util_ErrorChecker(eventDescription->createInstance(&eventInstance));
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
	return FMODGMS_Util_ErrorChecker(eventInstance->start());
}

// Sets pause state of an Event Instance.
double fmod_event_setPause(double handle, double paused) {
	getEventInstancefromHandle(handle);
	return FMODGMS_Util_ErrorChecker(eventInstance->setPaused(paused));
}

// Gets pause state of an Event Instance.
double fmod_event_getPause(double handle) {
	getEventInstancefromHandle(handle);
	bool paused = false;
	FMODGMS_Util_ErrorChecker(eventInstance->getPaused(&paused));
	return paused;
}

// Releases an Event Instance. 
double fmod_event_release(double handle) {
	getEventInstancefromHandle(handle);
	return FMODGMS_Util_ErrorChecker(eventInstance->release());
}

// Stops an Event Instance.
double fmod_event_stop(double handle, double instant) {
	getEventInstancefromHandle(handle);
	return FMODGMS_Util_ErrorChecker(eventInstance->stop((instant >= 1) ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT));
}

// Setting Event Instance Parameters.
double fmod_event_setParameter(double handle, const char* parameter_name, double value, double ignoreseek) {
	getEventInstancefromHandle(handle);
	return FMODGMS_Util_ErrorChecker(eventInstance->setParameterByName(parameter_name, value, ignoreseek));
}

// Getting Event Instance Parameters.
double fmod_event_getParameter(double handle, const char* parameter_name) {
	float value = 0.0f;
	float finalValue = 0.0f;
	getEventInstancefromHandle(handle);
	FMODGMS_Util_ErrorChecker(eventInstance->getParameterByName(parameter_name, &value, &finalValue));
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

	FMODGMS_Util_ErrorChecker(eventInstance->getPlaybackState(&playbackState));
	return playbackState;
}

// Setting Event Instance Timeline Position.
double fmod_event_setTimelinePosition(double handle, double timeline_pos) {
	getEventInstancefromHandle(handle);
	return FMODGMS_Util_ErrorChecker(eventInstance->setTimelinePosition(timeline_pos));
}

// Getting Event Instance Timeline Position.
double fmod_event_getTimelinePosition(double handle) {
	int timeline_pos;
	getEventInstancefromHandle(handle);
	FMODGMS_Util_ErrorChecker(eventInstance->getTimelinePosition(&timeline_pos));
	return timeline_pos;
}

// Get Event Instance Volume. 
double fmod_event_getVolume(double handle) {
	getEventInstancefromHandle(handle);
	float value = 0.0f;
	float finalValue = 0.0f;
	FMODGMS_Util_ErrorChecker(eventInstance->getVolume(&value, &finalValue));
	//double finalValue = finalValue;
	return finalValue;
}

// Set Event Instance Volume. 
double fmod_event_setVolume(double handle, double value) {
	getEventInstancefromHandle(handle);
	return FMODGMS_Util_ErrorChecker(eventInstance->setVolume(value));
}

// Get Event Instance Pitch. 
double fmod_event_getPitch(double handle) {
	getEventInstancefromHandle(handle);
	float value = 0.0f;
	float finalValue = 0.0f;
	FMODGMS_Util_ErrorChecker(eventInstance->getPitch(&value, &finalValue));
	//double finalValue = finalValue;
	return finalValue;
}

// Set Event Instance Pitch. 
double fmod_event_setPitch(double handle, double value) {
	getEventInstancefromHandle(handle);
	return FMODGMS_Util_ErrorChecker(eventInstance->setPitch(value));
}

// Get Event Instance Reverb. 
double fmod_event_getReverb(double handle/*, double index*/) {
	getEventInstancefromHandle(handle);
	float value = 0.0f;
	FMODGMS_Util_ErrorChecker(eventInstance->getReverbLevel(/*index*/ 0, &value));
	return value;
}

// Set Event Instance Reverb. 
double fmod_event_setReverb(double handle, /*double index,*/ double value) {
	getEventInstancefromHandle(handle);
	return FMODGMS_Util_ErrorChecker(eventInstance->setReverbLevel(/*index*/ 0, value));
}

// Sets pause state of all Event Instances.
double fmod_event_setPause_all(double paused) {
	EventInstHandles.ForEach([paused](double handle) {
		fmod_event_setPause(handle, paused);
		});
	return GM_true;
}

// Releases all Event Instances. 
double fmod_event_release_all() {
	EventInstHandles.ForEach([](double handle) {
		fmod_event_release(handle);
		});
	return GM_true;
}

// Stops all Event Instances.
double fmod_event_stop_all(double instant) {
	EventInstHandles.ForEach([instant](double handle) {
		fmod_event_setPause(handle, instant);
		});
	return GM_true;
}