#include "System.h"
#include "Events.h"
#include "3D Audio.h"

FMOD_3D_ATTRIBUTES listenerAttributes{
	{ 0.0f, 0.0f, 0.0f }, //position
	{ 0.0f, 0.0f, 0.0f }, //velocity
	{ 0.0f, 0.0f, 1.0f }, //forward
	{ 0.0f, 1.0f, 0.0f }  //up
};


// Set audio listener position.
double fmod_listener_setPosition(double listener, double x, double y, double z) {
	listenerAttributes.position = FMOD_VECTOR{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) };
	return FMODGMS_Util_ErrorChecker(FMODsystem->setListenerAttributes(listener, &listenerAttributes, nullptr));
}

// Get audio listener position.
char* fmod_listener_getPosition(double listener) { 
	FMOD_3D_ATTRIBUTES tempListenerAttributes{
		{ 0.0f, 0.0f, 0.0f }, //position
		{ 0.0f, 0.0f, 0.0f }, //velocity
		{ 0.0f, 0.0f, 1.0f }, //forward
		{ 0.0f, 1.0f, 0.0f }  //up
	};
	FMOD_RESULT result = FMODsystem->getListenerAttributes(listener, &tempListenerAttributes, nullptr);
	// Format the position values into a string
	char positionString[256];
	snprintf(positionString, sizeof(positionString), "%.2f, %.2f, %.2f", tempListenerAttributes.position.x, tempListenerAttributes.position.y, tempListenerAttributes.position.z);

	// Allocate memory for the string to be returned
	char* returnString = (char*)malloc(strlen(positionString) + 1);
	strcpy_s(returnString, 256, positionString);

	delete[] positionString;

	return returnString;
	delete[] returnString;
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
	return FMODGMS_Util_ErrorChecker(eventInstance->set3DAttributes(&tempListenerAttributes));
}
