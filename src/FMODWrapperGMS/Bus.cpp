#include "Bus.h"
#include "System.h"

bool busHandleValidityPredicate(FMOD::Studio::Bus* pointer)
{
	return pointer->isValid();
}
PointerHandleList<FMOD::Studio::Bus> BusHandleList = PointerHandleList<FMOD::Studio::Bus>(busHandleValidityPredicate);

 double fmod_getBus(const char* path) 
{
	FMOD::Studio::Bus* pBus = nullptr;

	FMODGMS_Util_ErrorChecker(pFMODSystem->getBus(path, &pBus));
	return BusHandleList.Add(pBus);
}

double fmod_bus_getVolume(double handle) 
{
	auto pBus = BusHandleList.Get(handle);
	float value = 0.0f;
	float finalValue = 0.0f;

	if (pBus == nullptr)
		return GM_error();

	FMODGMS_Util_ErrorChecker(pBus->getVolume(&value, &finalValue));
	return finalValue;
}

double fmod_bus_setVolume(double handle, double value) 
{
	auto pBus = BusHandleList.Get(handle);

	if (pBus == nullptr)
		return GM_error();

	return FMODGMS_Util_ErrorChecker(pBus->setVolume(value));
}

double fmod_bus_getMute(double handle) 
{
	auto pBus = BusHandleList.Get(handle);
	bool value = false;

	if (pBus == nullptr)
		return GM_error();

	FMODGMS_Util_ErrorChecker(pBus->getMute(&value));
	return value;
}

double fmod_bus_setMute(double handle, double value) 
{
	auto pBus = BusHandleList.Get(handle);

	if (pBus == nullptr)
		return GM_error();

	return FMODGMS_Util_ErrorChecker(pBus->setMute(value));
}
