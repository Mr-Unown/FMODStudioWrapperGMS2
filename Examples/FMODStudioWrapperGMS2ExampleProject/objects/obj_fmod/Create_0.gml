 show_debug_message("Created :  " + string(fmod_create()));
show_debug_message("Initialized :  " + string(fmod_init(32)));

var banks = 
[
"audio/Desktop/Master.strings.bank", 
"audio/Desktop/Master.bank", 
"audio/Desktop/Music.bank",
"audio/Desktop/SFX.bank"
]

for (var i = 0; i < array_length(banks); i++) {
    var b = (working_directory + banks[i]);
	var load_bank = fmod_loadBank(b);
    show_debug_message(string(banks[i]) + " :  "  + string(load_bank));
	fmod_loadBank(load_bank);
	
}

z = 0;
show_debug_message($"Listener Status: {fmod_listener_setPosition(0, x, y, z)}; Position: {x}, {y}, {z}");