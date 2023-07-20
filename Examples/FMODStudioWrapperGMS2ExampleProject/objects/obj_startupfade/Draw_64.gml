fade = approach(fade, fadeout, 0.01);

if(fade == 1 && fadeout) {
	room = Playground;
	fadeout = false;
}
if(fade == 0 && room == Playground)
	instance_destroy();

draw_set_alpha(fade);
draw_rectangle_color(0, 0, room_width, room_height, c_black, c_black, c_black, c_black, false);
draw_set_alpha(1);