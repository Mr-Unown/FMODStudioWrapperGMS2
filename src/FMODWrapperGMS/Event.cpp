#include "Event.h"
#include "System.h"

extern FMOD::Studio::EventDescription* pEventDescription = nullptr;
extern Handles<FMOD::Studio::EventInstance*> eventInstanceHandles{ };

extern FMOD_STUDIO_PLAYBACK_STATE playbackState = FMOD_STUDIO_PLAYBACK_STATE::FMOD_STUDIO_PLAYBACK_PLAYING;

double fmod_createEventInstance(const char* path) 
{
	pFMODSystem->getEvent(path, &pEventDescription);

	FMOD::Studio::EventInstance* pInstance = nullptr;

	FMODGMS_Util_ErrorChecker(pEventDescription->createInstance(&pInstance));
	return eventInstanceHandles.Add(pInstance);
}

double fmod_getEventLength(const char* path) 
{
	int event_length = 0;
	pFMODSystem->getEvent(path, &pEventDescription);
	pEventDescription->getLength(&event_length);
	return event_length;
}

#pragma region Playback
double fmod_event_play(double handle)
{
	auto pInstance = getEventInstancefromHandle(handle);

	if (pInstance == nullptr)
		return GM_error();

	return FMODGMS_Util_ErrorChecker(pInstance->start());
}

double fmod_event_setPause(double handle, double paused)
{
	auto pInstance = getEventInstancefromHandle(handle);

	if (pInstance == nullptr)
		return GM_error();

	return FMODGMS_Util_ErrorChecker(pInstance->setPaused(paused));
}

double fmod_event_getPause(double handle)
{
	auto pInstance = getEventInstancefromHandle(handle);

	if (pInstance == nullptr)
		return GM_error();

	bool paused = false;
	FMODGMS_Util_ErrorChecker(pInstance->getPaused(&paused));
	return paused;
}

double fmod_event_release(double handle)
{
	auto pInstance = getEventInstancefromHandle(handle);

	if (pInstance == nullptr)
		return GM_error();
	return FMODGMS_Util_ErrorChecker(pInstance->release());
}

double fmod_event_stop(double handle, double instant)
{
	auto pInstance = getEventInstancefromHandle(handle);

	if (pInstance == nullptr)
		return GM_error();

	return FMODGMS_Util_ErrorChecker(pInstance->stop((instant >= 1) ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT));
}

double fmod_event_getPlaybackState(double handle)
{
	auto temp = eventInstanceHandles.Get(handle);
	if (temp == nullptr) 
		return FMOD_STUDIO_PLAYBACK_STOPPED;
	
	
	if (!(*temp)->isValid()) 
	{
		eventInstanceHandles.Remove(handle);
		return FMOD_STUDIO_PLAYBACK_STOPPED;
	}
	FMODGMS_Util_ErrorChecker((*temp)->getPlaybackState(&playbackState));
	return playbackState;
}
#pragma endregion

double fmod_event_setParameter(double handle, const char* parameterName, double value, double ignoreSeek)
{
	auto pInstance = getEventInstancefromHandle(handle);

	if (pInstance == nullptr)
		return GM_error();

	return FMODGMS_Util_ErrorChecker(pInstance->setParameterByName(parameterName, value, ignoreSeek));
}

double fmod_event_getParameter(double handle, const char* parameterName)
{
	float value = 0.0f, finalValue = 0.0f;
	auto pInstance = getEventInstancefromHandle(handle);

	if (pInstance == nullptr)
		return GM_error();

	FMODGMS_Util_ErrorChecker(pInstance->getParameterByName(parameterName, &value, &finalValue));
	return finalValue;
}


double fmod_event_setTimelinePosition(double handle, double timelinePosition)
{
	auto pInstance = getEventInstancefromHandle(handle);

	if (pInstance == nullptr)
		return GM_error();

	return FMODGMS_Util_ErrorChecker(pInstance->setTimelinePosition(timelinePosition));
}

double fmod_event_getTimelinePosition(double handle) 
{
	int timeline_pos;
	auto pInstance = getEventInstancefromHandle(handle);

	if (pInstance == nullptr)
		return GM_error();

	FMODGMS_Util_ErrorChecker(pInstance->getTimelinePosition(&timeline_pos));
	return timeline_pos;
}


double fmod_event_setVolume(double handle, double value) 
{
	auto pInstance = getEventInstancefromHandle(handle);

	if (pInstance == nullptr)
		return GM_error();

	return FMODGMS_Util_ErrorChecker(pInstance->setVolume(value));
}

double fmod_event_getVolume(double handle) 
{
	auto pInstance = getEventInstancefromHandle(handle);
	float value = 0.0f, finalValue = 0.0f;

	if (pInstance == nullptr)
		return GM_error();

	FMODGMS_Util_ErrorChecker(pInstance->getVolume(&value, &finalValue));
	return finalValue;
}


double fmod_event_setPitch(double handle, double value)
{
	auto pInstance = getEventInstancefromHandle(handle);

	if (pInstance == nullptr)
		return GM_error();

	return FMODGMS_Util_ErrorChecker(pInstance->setPitch(value));
}

double fmod_event_getPitch(double handle) 
{
	auto pInstance = getEventInstancefromHandle(handle);
	float value = 0.0f, finalValue = 0.0f;

	if (pInstance == nullptr)
		return GM_error();

	FMODGMS_Util_ErrorChecker(pInstance->getPitch(&value, &finalValue));
	return finalValue;
}


double fmod_event_setReverb(double handle, /*double index,*/ double value)
{
	auto pInstance = getEventInstancefromHandle(handle);

	if (pInstance == nullptr)
		return GM_error();

	return FMODGMS_Util_ErrorChecker(pInstance->setReverbLevel(/*index*/ 0, value));
}

double fmod_event_getReverb(double handle/*, double index*/) 
{
	auto pInstance = getEventInstancefromHandle(handle);
	float value = 0.0f;

	if (pInstance == nullptr)
		return GM_error();

	FMODGMS_Util_ErrorChecker(pInstance->getReverbLevel(/*index*/ 0, &value));
	return value;
}