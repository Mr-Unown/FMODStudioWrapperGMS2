#include "System.h"
#include "Bank.h"

// Loads an FMOD Bank file.
double fmod_loadBank(const char* filename) {
	result = FMODsystem->loadBankFile(filename, FMOD_STUDIO_LOAD_BANK_NORMAL, &bankObject);
	FMODGMS_Util_ErrorChecker();
	return BankHandles.Add(bankObject);
}

// Loads FMOD Bank file Sample Data.
double fmod_bank_loadSampleData(double handle) {
	getBankfromHandle(handle);
	result = bankObject->loadSampleData();
	return FMODGMS_Util_ErrorChecker();
}

