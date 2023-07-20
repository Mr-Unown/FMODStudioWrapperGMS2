#include "System.h"
#include "Events.h"
#include "3D Audio.h"

// Set audio listener position.
double fmod_listener_setPosition(double listener, double x, double y, double z) {
	listenerAttributes.position = FMOD_VECTOR{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) };
	result = FMODsystem->setListenerAttributes(listener, &listenerAttributes, nullptr);
	return FMODGMS_Util_ErrorChecker();
}

// Get audio listener position.
double fmod_listener_getPosition(double listener) { // unfinished.
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
double fmod_event_set3DPosition(double handle, double x, double y, double z) {
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
