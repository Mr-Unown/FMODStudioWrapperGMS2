#pragma once

#include "Framework.h"

extern FMOD::Studio::System* pFMODSystem;
extern FMOD::System* pLowLevelSystem;
extern void* pExtraDriverData;
extern FMOD_REVERB_PROPERTIES reverbProperties; // TO DO: Add customization here.

// Creates the FMOD System.
GM_FUNC double fmod_create();

// Initializes the FMOD System.
GM_FUNC double fmod_init(double channelNumber);

// Updates the FMOD System.
GM_FUNC double fmod_update();

// Releases the FMOD System.
GM_FUNC double fmod_release();
