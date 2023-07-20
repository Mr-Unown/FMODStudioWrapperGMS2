#include "System.h"
#include "Bank.h"

FMOD::Studio::Bank* bankObject = nullptr;
Handles< FMOD::Studio::Bank* > BankHandles;


// Loads an FMOD Bank file.
double fmod_loadBank(const char* filename) {
	FMODGMS_Util_ErrorChecker(FMODsystem->loadBankFile(filename, FMOD_STUDIO_LOAD_BANK_NORMAL, &bankObject));
	return BankHandles.Add(bankObject);
}

// Loads FMOD Bank file Sample Data.
double fmod_bank_loadSampleData(double handle) {
	getBankfromHandle(handle);
	return FMODGMS_Util_ErrorChecker(bankObject->loadSampleData());
}

