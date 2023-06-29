#pragma once
#include "Framework.h"

extern FMOD_3D_ATTRIBUTES listenerAttributes;


// Set audio listener position.
GM_FUNC double fmod_listener_setPosition(double listener, double x, double y, double z = 0);
// Get audio listener position.
GM_FUNC double fmod_listener_getPosition(double listener);
// Set Event Instance 3D attributes.
GM_FUNC double fmod_event_set3DPosition(double handle, double x, double y, double z);