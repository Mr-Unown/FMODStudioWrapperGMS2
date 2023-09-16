#define fmod_bank_listEventPath
/// @param {real} id ds_list id.
/// @param {any*} bank_handle
var string_eventlist = ___INTERNAL_fmod_bank_listEventPath(argument1);
// Split the string by commas
var string_parts = string_split(string_eventlist, ",");
for (var i = 0; i < array_length(string_parts); ++i) {
	ds_list_add(argument0, string_parts[i]);
}
return ds_list_size(argument0);

#define fmod_listener_setPosition
/// @param {real} listener
/// @param {any*} x 
/// @param {any*} y 
/// @param {any*} [z] 
var listener = 0, xx = 0, yy = 0, zz = 0;
var listener = argument[0], xx = argument[1], yy = argument[2];
if (argument_count == 4) {
	zz = argument[3];
}

return ___INTERNAL_fmod_listener_setPosition(listener, xx, yy, zz);


#define fmod_listener_getPosition
/// @param {real} listener
// Create a struct to hold the position
var listener_position = {
    x : undefined,
    y : undefined,
    z : undefined
}
var string_listener = ___INTERNAL_fmod_listener_getPosition(argument0);
// Split the string by commas
var string_parts = string_split(string_listener, ",");
listener_position.x = real(string_parts[0]);
listener_position.y = real(string_parts[1]);
listener_position.z = real(string_parts[2]);
return listener_position;