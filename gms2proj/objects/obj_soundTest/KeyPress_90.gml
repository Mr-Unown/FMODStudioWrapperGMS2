/// @description Play Current Sound
if (!event_isplaying(eventHandleID)) {
	eventHandleID = fmod_createEventInstance(global.EventList[| soundIndex]);
	fmod_event_play(eventHandleID);
	currentX = irandom_range(0, room_width);
	currentY = irandom_range(0, room_height);
	fmod_event_set3DPosition(eventHandleID, currentX, currentY);
} else {
	fmod_event_release(eventHandleID);
	fmod_event_stop(eventHandleID, true);
	eventHandleID = undefined;

}













