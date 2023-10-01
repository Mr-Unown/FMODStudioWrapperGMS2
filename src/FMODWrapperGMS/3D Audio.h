#pragma once

#include "Framework.h"

extern FMOD_3D_ATTRIBUTES listenerAttributes;

// Set audio listener position.
GM_FUNC double fmod_listener_setPosition(double listener, double x, double y, double z = 0.0);

// Get audio listener position.
GM_FUNC char* fmod_listener_getPosition(double listener);

// Set audio listener velocity.
GM_FUNC double fmod_listener_setVelocity(double listener, double x, double y, double z);

// Get audio listener velocity.
GM_FUNC char* fmod_listener_getVelocity(double listener);

// Set Event Instance 3D position.
GM_FUNC double fmod_event_set3DPosition(double handle, double x, double y, double z = 0.0);

// Get Event Instance 3D position.
GM_FUNC char* fmod_event_get3DPosition(double handle);

// Set Event Instance 3D velocity.
GM_FUNC double fmod_event_set3DVelocity(double handle, double x, double y, double z);

// Get Event Instance 3D velocity.
GM_FUNC char* fmod_event_get3DVelocity(double handle);