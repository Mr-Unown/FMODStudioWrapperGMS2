#define fmod_init
/// @param numberofchannels
/// @param studioInitFlags=STUDIO_INIT_NORMAL;
/// @param {real} numberofchannels
/// @param {real} studioInitFlags
var numberofchannels = argument[0];
var studioInitFlags = argument_count > 1 ? argument[1] : STUDIO_INIT_NORMAL;;
// if (argument_count >= 2) {
// 	studioInitFlags = argument[1];
// }
return ___INTERNAL_fmod_init(numberofchannels, studioInitFlags);


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
/// @param listener
/// @param xx
/// @param yy
/// @param zz=0;


/// @param {real} listener
/// @param {any*} x 
/// @param {any*} y 
/// @param {any*} [z] 

var listener = argument[0], xx = argument[1], yy = argument[2];
var zz = argument_count > 3 ? argument[3] : 0;;
// if (argument_count >= 4) {
// 	zz = argument[3];
// }

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

#define fmod_listener_getVelocity
/// @param {real} listener
// Create a struct to hold the position
var listener_velocity = {
    x : undefined,
    y : undefined,
    z : undefined
}
var string_listener = ___INTERNAL_fmod_listener_getVelocity(argument0);
// Split the string by commas
var string_parts = string_split(string_listener, ",");
listener_velocity.x = real(string_parts[0]);
listener_velocity.y = real(string_parts[1]);
listener_velocity.z = real(string_parts[2]);
return listener_velocity;

#define fmod_event_set3DPosition
/// @param event_handle
/// @param xx
/// @param yy
/// @param zz=0;
var event_handle = argument[0], xx = argument[1], yy = argument[2];
var zz = argument_count > 3 ? argument[3] : 0;;
// if (argument_count >= 4) {
// 	zz = argument[3];
// }

return ___INTERNAL_fmod_event_set3DPosition(event_handle, xx, yy, zz);


#define fmod_event_get3DPosition
/// @param {real} event_handle
// Create a struct to hold the position
var listener_position = {
    x : undefined,
    y : undefined,
    z : undefined
}
var string_listener = ___INTERNAL_fmod_event_get3DPosition(argument0);
// Split the string by commas
var string_parts = string_split(string_listener, ",");
listener_position.x = real(string_parts[0]);
listener_position.y = real(string_parts[1]);
listener_position.z = real(string_parts[2]);
return listener_position;

#define fmod_event_get3DVelocity
/// @param {real} event_handle
// Create a struct to hold the position
var listener_velocity = {
    x : undefined,
    y : undefined,
    z : undefined
}
var string_listener = ___INTERNAL_fmod_event_get3DVelocity(argument0);
// Split the string by commas
var string_parts = string_split(string_listener, ",");
listener_velocity.x = real(string_parts[0]);
listener_velocity.y = real(string_parts[1]);
listener_velocity.z = real(string_parts[2]);
return listener_velocity;