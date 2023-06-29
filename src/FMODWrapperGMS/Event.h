#pragma once

#include "Framework.h"

extern FMOD::Studio::EventDescription* pEventDescription;
extern Handles<FMOD::Studio::EventInstance*> eventInstanceHandles;

extern FMOD_STUDIO_PLAYBACK_STATE playbackState;


inline FMOD::Studio::EventInstance* getEventInstancefromHandle(double handle)
{
	auto pointer = eventInstanceHandles.Get(handle);

	if (pointer == nullptr)
		return nullptr;

	if (!(*pointer)->isValid())
	{
		eventInstanceHandles.Remove(handle);
		return nullptr;;
	}

	return *pointer;
}

// Starts an Event Instance.
GM_FUNC double fmod_event_play(double handle);


// Creates an Event Instance.
GM_FUNC double fmod_createEventInstance(const char* path);

// Getting Event Length.
GM_FUNC double fmod_getEventLength(const char* path);

// Sets pause state of an Event Instance.
GM_FUNC double fmod_event_setPause(double handle, double paused);

// Gets pause state of an Event Instance.
GM_FUNC double fmod_event_getPause(double handle);

// Releases an Event Instance. 
GM_FUNC double fmod_event_release(double handle);

// Stops an Event Instance.
GM_FUNC double fmod_event_stop(double handle, double instant);

// Setting Event Instance Parameters.
GM_FUNC double fmod_event_setParameter(double handle, const char* parameterName, double value, double ignoreSeek = 0);

// Getting Event Instance Parameters.
GM_FUNC double fmod_event_getParameter(double handle, const char* parameterName);

// Getting Event Instance Playback State.
GM_FUNC double fmod_event_getPlaybackState(double handle);

// Setting Event Instance Timeline Position.
GM_FUNC double fmod_event_setTimelinePosition(double handle, double timelinePosition);

// Getting Event Instance Timeline Position.
GM_FUNC double fmod_event_getTimelinePosition(double handle);


// Set Event Instance Volume. 
GM_FUNC double fmod_event_setVolume(double handle, double value);

// Get Event Instance Volume. 
GM_FUNC double fmod_event_getVolume(double handle);


// Set Event Instance Pitch. 
GM_FUNC double fmod_event_setPitch(double handle, double value);

// Get Event Instance Pitch. 
GM_FUNC double fmod_event_getPitch(double handle);


// Set Event Instance Reverb. 
GM_FUNC double fmod_event_setReverb(double handle, /*double index,*/ double value);

// Get Event Instance Reverb. 
GM_FUNC double fmod_event_getReverb(double handle/*, double index*/);