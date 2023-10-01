/// @description Draw Current Playing Sound.
draw_text(0, 100, $"({soundIndex}) Current Event: {global.EventList[| soundIndex]}, Playing Status: {event_isplaying(eventHandleID) ? "Playing" : "Not Playing"}")

if (event_isplaying(eventHandleID)) {
	//var event_pos = fmod_event_get3DPosition(eventHandleID); extremely buggy.
	draw_text(currentX, currentY, "{}"); 
}




