#macro bbox_width (bbox_right - bbox_left)
#macro bbox_height (bbox_bottom - bbox_top)
/// @desc Initializes Collision Variables. To be used in Create Event.
function scr_collision_init() {

	usesCollision = true;
	grounded = false;
	groundedSlope = false;	
	terminalVelocity = 10;
	onMovingPlatform = noone;

	grav = 0;		
	hsp = 0;
	vsp = 0;
	prevHsp = 0;
	prevVsp = 0;	
	
	fracHsp = 0;
	fracVsp = 0;
}

/// @desc Handles Collision Physics.
function scr_collision() {
	grounded = false;
	groundedSlope = false;
	onMovingPlatform = noone;

	
	#region // Moving Platforms
	with (obj_movingPlatform) { 
		var _hspeed = (x - xprevious);
		var _vspeed = (y - yprevious);
		with (other.id) {
			x += _hspeed;
			y += _vspeed;
			if (place_meeting_collision(x, y + 1, ~Exclude.MOVING) && place_meeting(x, y + 1, other)) {
				onMovingPlatform = other.id;
			}
			x -= _hspeed;
			y -= _vspeed;			
		}
	}
	if (instance_exists(onMovingPlatform)) { // If collision with Moving Platform is detected, run kinematics.
		kinematics_movingPlatforms(id, onMovingPlatform, true);		
	}
	#endregion	
	
	// Subpixel Fix
	var true_hsp = hsp;
	var true_vsp = vsp;
	hsp = unown_absfloor(hsp);
	vsp = unown_absfloor(vsp);
	var wholePart = 0;
	fracHsp += (true_hsp - hsp); 
	
	if (abs(fracHsp) >= 1) {
	    wholePart = unown_absfloor(fracHsp);
	    hsp += wholePart;
	    fracHsp -= wholePart;
	}	
	fracVsp += (true_vsp - vsp);
	if (abs(fracVsp) >= 1) {
	    wholePart = unown_absfloor(fracVsp);
	    vsp += wholePart;
	    fracVsp -= wholePart;
	}	
	
	// Horizontal
	var move_hsp = clamp(abs(hsp), 0, bbox_width) * sign(hsp); // Calculate max units to move.
	repeat ceil((abs(hsp) / bbox_width)) { // Repeat per Bbox Width.
		if (!place_meeting_collision(x + move_hsp, y)) && !(place_meeting_collision(x, y + 1) && !place_meeting_collision(x + move_hsp, y + 1)) {			
			x += move_hsp;	
		} else { // If Collision is detected within Bbox Width.
			repeat(abs(move_hsp)) { // Do pixel by pixel check.
				
				
				// Move Up Slopes
				y -= slope_check_up(x + sign(move_hsp), y);
				// Move Down Slopes
				y += slope_check_down(x + sign(move_hsp), y);	
	
	
				// Move Down Upside Down Slopes
				y += reverseSlope_check_down(x + sign(move_hsp), y);
		
				// Move Up Upside Down Slopes
				if (vsp <= 0 && place_meeting_collision(x, y - 1)) {
					y -= reverseSlope_check_up(x + sign(move_hsp), y);
				}
				
				if (!place_meeting_collision(x + sign(move_hsp), y)) {
					x += sign(move_hsp); 
				} else {
					true_hsp = 0;
					move_hsp = 0;
					hsp = 0;
					break;
				}
			}
			break;
		}
	}

	// Vertical
	var move_vsp = clamp(abs(vsp), 0, bbox_height) * sign(vsp); // Calculate max units to move.
	repeat ceil((abs(vsp) / bbox_height)) { // Repeat per Bbox Height.
		if (!place_meeting_collision(x, y + move_vsp)) {
			y += move_vsp;	
		} else { // If Collision is detected within Bbox Height.
			repeat(abs(move_vsp)) { // Do pixel by pixel check.
				
				if (vsp < 0) {
					// Move Left Slopes
					x -= slope_check_left(x, y + sign(vsp));
					// Move Right Slopes
					x += slope_check_right(x, y + sign(vsp));
				}			
				
				if (!place_meeting_collision(x, y + sign(move_vsp))) {
					y += sign(move_vsp); 
				} else {
					true_vsp = 0;
					move_vsp = 0;
					vsp = 0;
					break;
				}
			}
			break;
		}
	}	

	
	hsp = true_hsp;
	vsp = true_vsp;	
	
	// Gravity
	if (vsp < terminalVelocity) {
		vsp += grav;
	}

	
	// Grounded Check
	grounded = (place_meeting_collision(x, y + 1));
	groundedSlope = (place_meeting_slope(x, y + 1));
	
	// Previous hsp and vsp
	prevHsp = hsp;
	prevVsp = vsp;	
}

/// @desc Handles movement of object affected by MOVING PLATFORMS.
/// @param {any*} obj The ID of the object affected.
/// @param {any*} platform_id The ID of the MOVING platform.
/// @param {bool} [collisions] Toggles checking of collisions.
function kinematics_movingPlatforms(obj, platform_id, collisions = true) {
	with (platform_id) {
		var _hsp = round(x - xprevious);
		var _vsp = round(y - yprevious);		
		if (!collisions) { // Ignore Collisions
			with (obj) {
				x += _hsp;
				y += _vsp;
			}
		} else { // Collision Checks
			with (obj) {
				repeat(abs(_hsp)) {	
					if (!place_meeting_collision(x + sign(_hsp), y)) {
						x += sign(_hsp); 
					} else {
						_hsp = 0;
						break;
					}
				}
				repeat(abs(_vsp)) {	
					if (!place_meeting_collision(x, y + sign(_vsp))) {
						y += sign(_vsp); 
					} else {
						_vsp = 0;
						break;
					}
				}
			}
		}
	}
}


/// @desc Returns by how much (in pixel) upwards until a valid surface is found. Used in slope collisions.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {real} [max_units] The max amount of pixels to check.
/// @returns {real}
function slope_check_up(x_pos, y_pos, max_units = 3) {
	// Move up slope
	for (var i = max_units; i > 0; --i) {
		var _check = true;
		var _z = (i - 1);
		repeat (i - 1) {
			if (!place_meeting_collision(x_pos, y_pos - _z)) {
				_check = false;
			}
			_z--;
		}
		if (place_meeting_collision(x_pos, y_pos) && _check && !place_meeting_collision(x_pos, y_pos - i)) {
			return i;
		}
	}
	return 0;	
}
	
/// @desc Returns by how much (in pixel) downwards until a valid surface is found. Used in slope collisions.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {real} [max_units] The max amount of pixels to check.
/// @returns {real}
function slope_check_down(x_pos, y_pos, max_units = 3) {
	// Move down slope
	for (var i = 1; i < max_units + 1; ++i) {
		var _check = true;
		var _z = 1;
		repeat (i) {
			if (place_meeting_collision(x_pos, y_pos + _z)) {
				_check = false;
			}
			_z++;
		}			
		if (!place_meeting_collision(x_pos, y_pos) && _check && place_meeting_collision(x_pos, y_pos + (i + 1))) {
			return i;
		}
	}	
	return 0;	
}
	
/// @desc Returns by how much (in pixel) to the left until a valid surface is found. Used in slope collisions.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {real} [max_units] The max amount of pixels to check.
/// @returns {real}
function slope_check_left(x_pos, y_pos, max_units = 3) {
	// Move to the left
	for (var i = 0; i < max_units; ++i) {
		if (place_meeting_collision(x_pos, y_pos) && !place_meeting_collision(x_pos - i, y_pos)) {
			return i;
		}
	}
	return 0;	
}
	
/// @desc Returns by how much (in pixel) to the right until a valid surface is found. Used in slope collisions.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {real} [max_units] The max amount of pixels to check.
/// @returns {real}
function slope_check_right(x_pos, y_pos, max_units = 3) {
	// Move to the Right
	for (var i = 0; i < max_units; ++i) {
		if (place_meeting_collision(x_pos, y_pos) && !place_meeting_collision(x_pos + i, y_pos)) {
			return i;
		}
	}
	return 0;		
}	

/// @desc Returns by how much (in pixel) going down until a valid surface is found. Used in slope collisions.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {real} [max_units] The max amount of pixels to check.
/// @returns {real}
function reverseSlope_check_down(x_pos, y_pos, max_units = 3) {
	// Move to the Bottom
	for (var i = 0; i < max_units; ++i) {
		if (place_meeting_collision(x_pos, y_pos) && !place_meeting_collision(x_pos, y_pos + i)) {
			return i;
		}
	}
	return 0;	
}
	
/// @desc Returns by how much (in pixel) going up until a valid surface is found. Used in slope collisions.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {real} [max_units] The max amount of pixels to check.
/// @returns {real}
function reverseSlope_check_up(x_pos, y_pos, max_units = 3) {
	// Move to the Top
	for (var i = 0; i < max_units; ++i) {
		if (!place_meeting_collision(x_pos, y_pos) && !place_meeting_collision(x_pos, y_pos - i) && place_meeting_collision(x_pos, y_pos - (i + 1))) {
			return i;
		}		
	}
	return 0;		
}	