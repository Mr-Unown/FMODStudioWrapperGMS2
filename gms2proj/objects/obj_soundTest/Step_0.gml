/// @description Cycle through Sound.
if (!event_isplaying(eventHandleID)) {
	soundIndex += (keyboard_check_pressed(vk_down)) - (keyboard_check_pressed(vk_up));

	soundIndex = clamp(soundIndex, 0, ds_list_size(global.EventList) - 1);
}