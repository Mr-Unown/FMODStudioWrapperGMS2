scr_collision();
if(grounded) {
	vsp = -4;
	event_play_at(metalclanksnd, x, y)
}

fmod_event_set3DPosition(bombtickingsnd, x, y, 0);
// Increase pitch as time runs out.
var bomb_pitch = ((timerMax - timer) / timerMax) * 0.5;
fmod_event_setPitch(bombtickingsnd, 1 + bomb_pitch); 
timer = approach(timer, 0, 1);

if((timer == 0 && grounded) || keyboard_check_pressed(ord("C")))
	instance_destroy();