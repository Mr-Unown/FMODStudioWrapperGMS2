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
	FMOD_RESULT result = FMODsystem->getListenerAttributes(listener, &listenerAttributes, nullptr);
	listenerAttributes.position = FMOD_VECTOR{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) };
	return FMODGMS_Util_ErrorChecker(FMODsystem->setListenerAttributes(listener, &listenerAttributes, nullptr));
}

// Get audio listener position.
char* fmod_listener_getPosition(double listener) { 
	FMOD_3D_ATTRIBUTES tempListenerAttributes;
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

// Set audio listener velocity.
double fmod_listener_setVelocity(double listener, double x, double y, double z) {
	FMOD_RESULT result = FMODsystem->getListenerAttributes(listener, &listenerAttributes, nullptr);
	listenerAttributes.velocity = FMOD_VECTOR{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) };
	return FMODGMS_Util_ErrorChecker(FMODsystem->setListenerAttributes(listener, &listenerAttributes, nullptr));
}

// Get audio listener velocity.
char* fmod_listener_getVelocity(double listener) {
	FMOD_3D_ATTRIBUTES tempListenerAttributes;
	FMOD_RESULT result = FMODsystem->getListenerAttributes(listener, &tempListenerAttributes, nullptr);
	// Format the velocity values into a string
	char positionString[256];
	snprintf(positionString, sizeof(positionString), "%.2f, %.2f, %.2f", tempListenerAttributes.velocity.x, tempListenerAttributes.velocity.y, tempListenerAttributes.velocity.z);

	// Allocate memory for the string to be returned
	char* returnString = (char*)malloc(strlen(positionString) + 1);
	strcpy_s(returnString, 256, positionString);

	delete[] positionString;

	return returnString;
	delete[] returnString;
}


// Set Event Instance 3D position.
double fmod_event_set3DPosition(double handle, double x, double y, double z) {
	FMOD_3D_ATTRIBUTES tempListenerAttributes;
	getEventInstancefromHandle(handle);
	eventInstance->get3DAttributes(&tempListenerAttributes);
	tempListenerAttributes.position = FMOD_VECTOR{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) };
	return FMODGMS_Util_ErrorChecker(eventInstance->set3DAttributes(&tempListenerAttributes));
}

// Get Event Instance 3D position.
char* fmod_event_get3DPosition(double handle) {
	FMOD_3D_ATTRIBUTES tempEventAttributes;
	getEventInstancefromHandle(handle);
	eventInstance->get3DAttributes(&tempEventAttributes);

	// Format the position values into a string
	char positionString[256];
	snprintf(positionString, sizeof(positionString), "%.2f, %.2f, %.2f", tempEventAttributes.position.x, tempEventAttributes.position.y, tempEventAttributes.position.z);

	// Allocate memory for the string to be returned
	char* returnString = (char*)malloc(strlen(positionString) + 1);
	strcpy_s(returnString, 256, positionString);

	delete[] positionString;

	return returnString;
	delete[] returnString;
}


// Set Event Instance 3D velocity.
double fmod_event_set3DVelocity(double handle, double x, double y, double z) {
	FMOD_3D_ATTRIBUTES tempListenerAttributes;
	getEventInstancefromHandle(handle);
	eventInstance->get3DAttributes(&tempListenerAttributes); 
	tempListenerAttributes.velocity = FMOD_VECTOR{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) };

	return FMODGMS_Util_ErrorChecker(eventInstance->set3DAttributes(&tempListenerAttributes));
}

// Get Event Instance 3D velocity.
char* fmod_event_get3DVelocity(double handle) {
	FMOD_3D_ATTRIBUTES tempEventAttributes;
	getEventInstancefromHandle(handle);
	eventInstance->get3DAttributes(&tempEventAttributes);

	// Format the velocity values into a string
	char positionString[256];
	snprintf(positionString, sizeof(positionString), "%.2f, %.2f, %.2f", tempEventAttributes.velocity.x, tempEventAttributes.velocity.y, tempEventAttributes.velocity.z);

	// Allocate memory for the string to be returned
	char* returnString = (char*)malloc(strlen(positionString) + 1);
	strcpy_s(returnString, 256, positionString);

	delete[] positionString;

	return returnString;
	delete[] returnString;
}