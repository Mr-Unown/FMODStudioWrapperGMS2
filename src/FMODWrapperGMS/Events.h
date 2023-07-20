#pragma once

#include "Framework.h"

FMOD::Studio::EventDescription* eventDescription = nullptr;
FMOD::Studio::EventInstance* eventInstance = nullptr;
Handles< FMOD::Studio::EventInstance* > EventInstHandles;
FMOD_STUDIO_PLAYBACK_STATE playbackState;

// Creates an Event Instance.
GM_FUNC double fmod_createEventInstance(const char* path);

// Getting Event Length.
GM_FUNC double fmod_getEventLength(const char* path);

// Starts an Event Instance.
GM_FUNC double fmod_event_play(double handle);

// Sets pause state of an Event Instance.
GM_FUNC double fmod_event_setPause(double handle, double paused);

// Gets pause state of an Event Instance.
GM_FUNC double fmod_event_getPause(double handle);

// Releases an Event Instance. 
GM_FUNC double fmod_event_release(double handle);

// Stops an Event Instance.
GM_FUNC double fmod_event_stop(double handle, double instant);

// Setting Event Instance Parameters.
GM_FUNC double fmod_event_setParameter(double handle, const char* parameter_name, double value, double ignoreseek = 0);

// Getting Event Instance Parameters.
GM_FUNC double fmod_event_getParameter(double handle, const char* parameter_name);

// Getting Event Instance Playback State.
GM_FUNC double fmod_event_getPlaybackState(double handle);

// Setting Event Instance Timeline Position.
GM_FUNC double fmod_event_setTimelinePosition(double handle, double timeline_pos);

// Getting Event Instance Timeline Position.
GM_FUNC double fmod_event_getTimelinePosition(double handle);

// Get Event Instance Volume. 
GM_FUNC double fmod_event_getVolume(double handle);

// Set Event Instance Volume. 
GM_FUNC double fmod_event_setVolume(double handle, double value);

// Get Event Instance Pitch. 
GM_FUNC double fmod_event_getPitch(double handle);

// Set Event Instance Pitch. 
GM_FUNC double fmod_event_setPitch(double handle, double value);

// Get Event Instance Reverb. 
GM_FUNC double fmod_event_getReverb(double handle/*, double index*/);

// Set Event Instance Reverb. 
GM_FUNC double fmod_event_setReverb(double handle, /*double index,*/ double value);

// Sets pause state of all Event Instances.
GM_FUNC double fmod_event_setPause_all(double paused);

// Releases all Event Instances. 
GM_FUNC double fmod_event_release_all();

// Stops all Event Instances.
GM_FUNC double fmod_event_stop_all(double instant);


// Inline Function.
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