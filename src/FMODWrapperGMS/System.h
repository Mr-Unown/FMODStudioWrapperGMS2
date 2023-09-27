#pragma once

#include "Framework.h"

extern FMOD::Studio::System* FMODsystem;
extern FMOD::System* lowLevelSystem;
extern FMOD_REVERB_PROPERTIES reverbProperties;
extern void* extraDriverData;


// Creates the FMOD System.
GM_FUNC double fmod_create();

// Initializes the FMOD System.
GM_FUNC double fmod_init(double numberofchannels, double studioInitFlags = FMOD_STUDIO_INIT_NORMAL);

// Updates the FMOD System.
GM_FUNC double fmod_update();

// Releases the FMOD System.
GM_FUNC double fmod_release();

// Setting Global Parameters.
GM_FUNC double fmod_global_setParameter(const char* parameter_name, double value, double ignoreseek);

// Getting Global Parameters.
GM_FUNC double fmod_global_getParameter(const char* parameter_name);