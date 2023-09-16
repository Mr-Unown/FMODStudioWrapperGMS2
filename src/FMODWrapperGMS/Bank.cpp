#include "System.h"
#include "Bank.h"
#include <cstring>
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

// Returns a ds_list of every single event path within a bank file.
char* fmod_bank_listEventPath(double handle) {
    getBankfromHandle(handle);

    // Get the event count
    int eventCount = 0;
    bankObject->getEventCount(&eventCount);

    // Retrieve the event list
    FMOD::Studio::EventDescription** eventArray = new FMOD::Studio::EventDescription * [eventCount];
    bankObject->getEventList(eventArray, eventCount, nullptr);

    // Calculate the total length of the event paths
    int totalLength = 0;
    for (int i = 0; i < eventCount; i++) {
        char* path = new char[256];
        eventArray[i]->getPath(path, 256, nullptr);
        totalLength += strlen(path) + 1; // +1 for the comma separator
        delete[] path; // Free the memory allocated for path
    }

    // Allocate memory for the result string
    char* result = new char[totalLength];
    result[0] = '\0'; // Initialize the result string as an empty string

    // Concatenate the event paths with commas
    for (int i = 0; i < eventCount; i++) {
        char* path = new char[256];
        eventArray[i]->getPath(path, 256, nullptr);
        strcat_s(result, totalLength, path);
        if (i < eventCount - 1) {
            strcat_s(result, totalLength, ",");
        }
        delete[] path; // Free the memory allocated for path
    }

    // Clean up the event array
    delete[] eventArray;

    return result;
    delete[] result;
}