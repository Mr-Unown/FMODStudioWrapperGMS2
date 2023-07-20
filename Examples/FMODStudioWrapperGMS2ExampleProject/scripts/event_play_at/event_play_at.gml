// Script assets have changed for v2.3.0 see
// https://help.yoyogames.com/hc/en-us/articles/360005277377 for more information
function event_play_at(event_handle, _x, _y, _z = 0){
	fmod_event_set3DPosition(event_handle, _x, _y, _z)
	fmod_event_play(event_handle)
}