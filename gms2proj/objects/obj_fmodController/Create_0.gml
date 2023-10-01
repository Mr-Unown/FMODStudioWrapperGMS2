/// @description Initialize FMOD system. Loads Banks.
global.BankArray = [];

var fmod_created = fmod_create(); // Create FMOD System.
show_debug_message($"Created FMOD System :  {fmod_created}"); 

/* FMOD Init Flags. (Use Bitwise.)
STUDIO_INIT_NORMAL                0x00000000 Use defaults for all initialization options.
STUDIO_INIT_LIVEUPDATE            0x00000001 Enable live update.
STUDIO_INIT_ALLOW_MISSING_PLUGINS 0x00000002 Load banks even if they reference plugins that have not been loaded.
STUDIO_INIT_SYNCHRONOUS_UPDATE    0x00000004 Disable asynchronous processing and perform all processing on the calling thread instead.
STUDIO_INIT_DEFERRED_CALLBACKS    0x00000008 Defer timeline callbacks until the main update. See Studio::EventInstance::setCallback for more information.
STUDIO_INIT_LOAD_FROM_UPDATE      0x00000010 No additional threads are created for bank and resource loading. Loading is driven from Studio::System::update.
STUDIO_INIT_MEMORY_TRACKING       0x00000020 Enables detailed memory usage statistics. Increases memory footprint and impacts performance. See Studio::Bus::getMemoryUsage and Studio::EventInstance::getMemoryUsage for more information. Implies FMOD_INIT_MEMORY_TRACKING.
*/
var fmod_initialized = fmod_init(64, STUDIO_INIT_NORMAL & STUDIO_INIT_LIVEUPDATE); // Initialize FMOD System. 
show_debug_message($"Initialized FMOD System :  {fmod_initialized}");


var bank_file_paths = [
	"audio/Desktop/Master.strings.bank", 
	"audio/Desktop/Master.bank", 
	"audio/Desktop/Music.bank",
	"audio/Desktop/SFX.bank"
];

for (var i = 0; i < array_length(bank_file_paths); i++) {
	var b = (working_directory + bank_file_paths[i]);
	global.BankArray[i] = fmod_loadBank(b); // Load Bank File and store Handle to global.BankArray.
	show_debug_message($"Bank File ({bank_file_paths[i]}) :  {global.BankArray[i]}");
	show_debug_message($"Bank Sample Data ({bank_file_paths[i]}) LOADED? :  ({fmod_bank_loadSampleData(global.BankArray[i])})");
}
global.EventList = ds_list_create();
for (var i = 0; i < array_length(global.BankArray); i++) {
	fmod_bank_listEventPath(global.EventList, global.BankArray[i]);
}

instance_create_depth(0,0, -5, obj_soundTest);