#pragma once

#include "framework.h"

FMOD_3D_ATTRIBUTES listenerAttributes{
	{ 0.0f, 0.0f, 0.0f }, //position
	{ 0.0f, 0.0f, 0.0f }, //velocity
	{ 0.0f, 0.0f, 1.0f }, //forward
	{ 0.0f, 1.0f, 0.0f }  //up
};

// Set audio listener position.
GM_FUNC double fmod_listener_setPosition(double listener, double x, double y, double z = 0);

// Get audio listener position.
GM_FUNC double fmod_listener_getPosition(double listener);

// Set Event Instance 3D attributes.
GM_FUNC double fmod_event_set3DPosition(double handle, double x, double y, double z);