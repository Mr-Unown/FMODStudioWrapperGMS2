scr_collision();
if(grounded) {
	vsp = -4;
	event_play_at(metalclanksnd, x, y)
}

fmod_event_set3DPosition(bombtickingsnd, x, y, 0);

timer = approach(timer, 0, 1);

if((timer == 0 && grounded) || keyboard_check_pressed(ord("C")))
	instance_destroy();