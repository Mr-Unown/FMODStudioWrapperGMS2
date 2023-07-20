#pragma once

#include "framework.h"

FMOD::Studio::System* FMODsystem = nullptr;
FMOD::System* lowLevelSystem = nullptr;
FMOD_REVERB_PROPERTIES reverbProperties = FMOD_PRESET_GENERIC;

// Creates the FMOD System.
GM_FUNC double fmod_create();

// Initializes the FMOD System.
GM_FUNC double fmod_init(double numberofchannels);

// Updates the FMOD System.
GM_FUNC double fmod_update();

// Releases the FMOD System.
GM_FUNC double fmod_release();

// Setting Global Parameters.
GM_FUNC double fmod_global_setParameter(const char* parameter_name, double value, double ignoreseek = 0);

// Getting Global Parameters.
GM_FUNC double fmod_global_getParameter(const char* parameter_name);