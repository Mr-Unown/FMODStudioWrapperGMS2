#include "Bank.h"
#include "System.h"


Handles<FMOD::Studio::Bank*> bankHandles{ };

double fmod_loadBank(const char* filename) 
{
	FMOD::Studio::Bank* pBank = nullptr;

	// RadixComet: I dunno why Unown is getting this?? lmfao
	auto errorResult = FMODGMS_Util_ErrorChecker(pFMODSystem->loadBankFile(filename, FMOD_STUDIO_LOAD_BANK_NORMAL, &pBank));

	return bankHandles.Add(pBank);
}

double fmod_bank_loadSampleData(double handle) 
{
	FMOD::Studio::Bank* pBank = getBankfromHandle(handle);

	if (pBank == nullptr)
		return GM_error();

	return FMODGMS_Util_ErrorChecker(pBank->loadSampleData());
}

double fmod_global_setParameter(const char* parameterName, double value, double ignoreSeek) 
{
	return FMODGMS_Util_ErrorChecker(pFMODSystem->setParameterByName(parameterName, value, ignoreSeek));
}

double fmod_global_getParameter(const char* parameterName) 
{
	float value = 0.0f;
	float finalValue = 0.0f;
	FMODGMS_Util_ErrorChecker(pFMODSystem->getParameterByName(parameterName, &value, &finalValue));

	return finalValue;
}
