#include "System.h"

FMOD::Studio::System* pFMODSystem = nullptr;
FMOD::System* pLowLevelSystem = nullptr;
void* pExtraDriverData = nullptr;
FMOD_REVERB_PROPERTIES reverbProperties = FMOD_PRESET_GENERIC; // TO DO: Add customization here.

double fmod_create() 
{
	return FMODGMS_Util_ErrorChecker(FMOD::Studio::System::create(&pFMODSystem));
}

double fmod_init(double channelNumber) 
{
	FMOD_RESULT result = pFMODSystem->initialize(channelNumber, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, pExtraDriverData);
	pFMODSystem->getCoreSystem(&pLowLevelSystem);

	pLowLevelSystem->setReverbProperties(0, &reverbProperties);

	return FMODGMS_Util_ErrorChecker(result);
}

double fmod_update() 
{
	return FMODGMS_Util_ErrorChecker(pFMODSystem->update());
}

// TODO: Add fmod_cleanup() using for each

double fmod_release() 
{
	return FMODGMS_Util_ErrorChecker(pFMODSystem->release());
}
