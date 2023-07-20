move = -keyboard_check(vk_left) + keyboard_check(vk_right);

scr_collision();

switch(state) {
	case States.Normal:
		hsp = move * 1.6;

		if(move != 0) {
			sprite_index = spr_robo_walk;
			xscale = move;
			if(floor(image_index) == 2 || floor(image_index) == 5) {
				if(!stepped) {
					event_play_at(metalclanksnd, x, y);
					stepped = true;
				}
			}
			else
				stepped = false;
		}
		else
			sprite_index = spr_robo_idle;
		
		if(keyboard_check(vk_down)) {
			state = States.Crouch;
			sprite_index = spr_robo_crouch;
			image_index = 1;
		}
		
		if(!grounded)
			state = States.Flying;
		
		image_speed = 1;
		break;
	case States.Crouch:
		hsp = approach(hsp, move * 2, 0.1);
	
		if(floor(image_index) == image_number - 1 && sprite_index != spr_robo_roll)
			sprite_index = spr_robo_crouchend;
		
		if(move != 0) {
			xscale = move;
			if(sprite_index != spr_robo_crouch) {
				sprite_index = spr_robo_roll;
			
				var ind = floor(image_index) mod 1
				if(ind = 0 && grounded) {
					vsp = -2;
					event_play_at(metalclanksnd, x, y);
				}
			}
		}
		else {
			if(sprite_index != spr_robo_bombdispense && sprite_index != spr_robo_crouch && grounded)
				sprite_index = spr_robo_crouchend;
			if(!grounded)
				sprite_index = spr_robo_roll;
		}
			
		if(keyboard_check_pressed(ord("X")) && sprite_index != spr_robo_bombdispense) {
			image_index = 0;
			sprite_index = spr_robo_bombdispense;
		}
		
		if(floor(image_index) == 1 && sprite_index == spr_robo_bombdispense) {
			if(!dispensed) {
				event_play_at(dispensesnd, x, y)
				instance_create_depth(x, y, depth + 1, obj_bomb);
				dispensed = true;
			}
		}
		else
			dispensed = false;
			
		if(!keyboard_check(vk_down) && grounded) {
			vsp = 0;
			state = States.Normal;
		}
		
		image_speed = 1;
		break;
	case States.Flying:
		sprite_index = spr_robo_roll;
	
		if(place_meeting_collision(x, y + 1))
			hsp = approach(hsp, 0, 0.25);

		if(place_meeting_collision(x + hsp, y)) {
			if(hsp > 3 && sign(hsp) == 1 || hsp < -3 && sign(hsp) == -1) {
				hsp = round(-(hsp / 2));
				event_play_at(metalclanksnd, x, y);
			}
			else
				hsp = 0;
		}
		if(place_meeting_collision(x, y + vsp)) {
			if(vsp > 3 && sign(vsp) == 1 || vsp < -3 && sign(vsp) == -1) {
				vsp = round(-(vsp / 2));
				event_play_at(metalclanksnd, x, y);
			}
			else
				vsp = 0;
		}
		
		if(hsp == 0 && grounded) {
			if(keyboard_check(vk_down)) {
				state = States.Crouch;
				sprite_index = spr_robo_crouchend;
			}
			else
				state = States.Normal;
		}
			
		image_speed = vsp;
		break
}

if(state == 1)
	mask_index = spr_robo_maskcrouch;
else
	mask_index = spr_robo_mask;

fmod_listener_setPosition(0, x, y, 0);