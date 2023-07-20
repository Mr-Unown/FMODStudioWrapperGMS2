#region Flags for Excluding specific types of Collision Object.
enum Exclude {
	NONE = 0, 
	SLOPES = 1,
	SOLIDS = 2,
	MOVING = 4,
	PLATFORMS = 8,
	ALL = 15 
}
#endregion

// Create DS_list for collisions
global.MyCollisionList = ds_list_create();

#region Collisions
/// @desc With this function you can check a place for collision objects. 
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {ID.DsList} list The DS list to use to store the IDs of colliding platforms.
/// @param {real} [exclude] Using the EXLCUDE flags you can exclude types of objects. Ex: (Exclude.SLOPES|Exclude.PLATFORMS). You can also invert it like so: (~Exclude.MOVING).
/// @returns {real} The number of instances found to be in collision.
function instance_place_list_collision(xx, yy, exclude = Exclude.NONE, list = undefined) {
	var collided = 0;
	// Exclude specific types of collisions
	var 
	check_slopes = Exclude.SLOPES&exclude != Exclude.SLOPES,
	check_solids = Exclude.SOLIDS&exclude != Exclude.SOLIDS,
	check_platforms = Exclude.PLATFORMS&exclude != Exclude.PLATFORMS,
	check_moving = Exclude.MOVING&exclude != Exclude.MOVING;

	
	if (check_solids) { // Basic Solid Collisions and Backside of Slopes
		collided += instance_place_list_solid(xx, yy, list);
		collided += instance_place_list_slopeSolid(xx, yy, list);
	}
	
	if (check_slopes) { // Sloped Collisions
		
		if (check_solids) {
			collided += instance_place_list_slope(xx, yy, list);
		}
		
		if (check_platforms) {
			collided += instance_place_list_slopePlatform(xx, yy, list);		
		}
	}
	if (check_platforms) { // Semisolid Collisions
		collided += instance_place_list_platform(xx, yy, list);
		collided += instance_place_list_sidePlatform(xx, yy, list);
	}
	if (check_moving) { // Moving Platforms
		collided += instance_place_list_movingPlatform(xx, yy, list);
	}
	return collided;
}
/// @desc With this function you can check a place for collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {real} [exclude] Using the EXLCUDE flags you can exclude types of objects. Ex: (Exclude.SLOPES|Exclude.PLATFORMS). You can also invert it like so: (~Exclude.MOVING).
/// @returns {bool}
function place_meeting_collision(xx, yy, exclude = Exclude.NONE) {
	// Exclude specific types of collisions
	var 
	check_slopes = Exclude.SLOPES&exclude != Exclude.SLOPES,
	check_solids = Exclude.SOLIDS&exclude != Exclude.SOLIDS,
	check_platforms = Exclude.PLATFORMS&exclude != Exclude.PLATFORMS,
	check_moving = Exclude.MOVING&exclude != Exclude.MOVING;

	
	if (check_solids) { // Basic Solid Collisions and Backside of Slopes
		if (place_meeting_solid(xx, yy)) { // Basic Solids			
			return true;
		}		

		if (place_meeting_slopeSolid(xx, yy)) { // Slope Backsides
			return true;
		}		
	}
	
	if (check_slopes) { // Sloped Collisions
		
		if (check_solids) {
			if (place_meeting_slope(xx, yy, false)) { // Basic Slope Collisions
				return true;
			}
		}
		
		if (check_platforms) {
			if (place_meeting_slopePlatform(xx, yy)) { // Sloped Semisolid Collisions
				return true;
			}			
		}
	}
	if (check_platforms) { // Semisolid Collisions
		if (place_meeting_platform(xx, yy)) {
			return true;
		}
		if (place_meeting_sidePlatform(xx, yy)) {
			return true;
		}
	}
	if (check_moving) { // Moving Platforms
		if (place_meeting_movingPlatform(xx, yy)) {
			return true;
		}
	}
	return false;
}	
/// @desc With this function you can check a position for collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {real} [exclude] Using the EXLCUDE flags you can exclude types of objects. Ex: (Exclude.SLOPES|Exclude.PLATFORMS). You can also invert it like so: (~Exclude.MOVING).
/// @returns {bool}
function position_meeting_collision(xx, yy, exclude = Exclude.NONE) {
	var old_mask = mask_index;
	mask_index = spr_unownPixel;
	var check_collision = (place_meeting_collision(xx, yy, exclude));	
	mask_index = old_mask;
	return check_collision;	
}	
#endregion

#region Solids
/// @desc With this function you can check a place for basic solid collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject|Id.Instance} [obj] The object to check for. (Optional)
/// @param {ID.DsList} [list] The DS list to use to store the IDs of colliding solids. (Optional)
/// @returns {real} The number of instances found to be in collision.
function instance_place_list_solid(xx, yy, obj = obj_solid, list = undefined) {
	if (place_meeting(xx, yy, obj)) { // Basic Solids		
		var solid_number = instance_place_list(xx, yy, obj, global.MyCollisionList, false);
		var collided = 0;
		if (solid_number > 0) {
			for (var i = 0; i < solid_number; ++i;) {
				var solid_object = (global.MyCollisionList[| i]);
				
				var _can_collide = true;
				if (variable_instance_exists(solid_object, "canCollide")) {
					_can_collide = solid_object.canCollide(object_index);
				}
				
				if (_can_collide == true) {				
					collided++;
					if (!is_undefined(list)) { // Add to List
						ds_list_add(list, solid_object.id);
					} else {
						break;
					}
				}	
			}
		}
		ds_list_clear(global.MyCollisionList);
		if (collided > 0) {	
			return (collided);
		}		
	}	
	return 0;
}
/// @desc With this function you can check a place for basic solid collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject|Id.Instance} [obj] The object to check for. (Optional)
/// @returns {bool}
function place_meeting_solid(xx, yy, obj = obj_solid) {
	return (instance_place_list_solid(xx, yy, obj) > 0);
}
/// @desc With this function you can check a position for basic solid collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject|Id.Instance} [obj] The object to check for. (Optional)
/// @returns {bool}
function position_meeting_solid(xx, yy, obj = obj_solid) {
	var old_mask = mask_index;
	mask_index = spr_unownPixel;
	var check_collision = (instance_place_list_solid(xx, yy, obj) > 0);
	mask_index = old_mask;
	return check_collision;
}
#endregion

#region Platforms
/// @desc With this function you can check a place for platform collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject|Id.Instance} [obj] The object to check for. (Optional)
/// @param {ID.DsList} [list] The DS list to use to store the IDs of colliding platforms. (Optional)
/// @returns {real} The number of instances found to be in collision.
function instance_place_list_platform(xx, yy, obj = obj_platform, list = undefined) {
	var collided = 0;
	if (place_meeting(xx, yy, obj)) { // Basic platforms		
		var platform_number = instance_place_list(xx, yy, obj, global.MyCollisionList, false);
		if (platform_number > 0) {
			for (var i = 0; i < platform_number; ++i;) {
				var platform_object = (global.MyCollisionList[| i]);
				
				var _can_collide = true;
				if (variable_instance_exists(platform_object, "canCollide")) {
					_can_collide = platform_object.canCollide(object_index);
				}
				var _check = (sign(platform_object.image_yscale) <= -1 ? yy <= y : yy > y);			
				if (_check == true && _can_collide && place_meeting(xx, yy, platform_object) && !place_meeting(xx, y, platform_object)) {			
					collided++;
					if (!is_undefined(list)) { // Add to List
						ds_list_add(list, platform_object.id);
					} else {
						break;
					}
				}	
			}
		}
		ds_list_clear(global.MyCollisionList);
		if (collided > 0) {	
			return (collided);
		}		
	}	
	return 0;
}
/// @desc With this function you can check a place for side platform collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject|Id.Instance} [obj] The object to check for. (Optional)
/// @param {ID.DsList} [list] The DS list to use to store the IDs of colliding platforms. (Optional)
/// @returns {real} The number of instances found to be in collision.
function instance_place_list_sidePlatform(xx, yy, obj = obj_sidePlatform, list = undefined) {
	var collided = 0;
	if (place_meeting(xx, yy, obj)) { // Basic Side Platforms		
		var side_platform_number = instance_place_list(xx, yy, obj, global.MyCollisionList, false);
		if (side_platform_number > 0) {
			for (var i = 0; i < side_platform_number; ++i;) {
				var side_platform_object = (global.MyCollisionList[| i]);
				
				var _can_collide = true;
				if (variable_instance_exists(side_platform_object, "canCollide")) {
					_can_collide = side_platform_object.canCollide(object_index);
				}
				var _check = (sign(side_platform_object.image_xscale) < 0 ? xx >= x : xx <= x);			
				if (_check == true && _can_collide && place_meeting(xx, yy, side_platform_object) && !place_meeting(x, yy, side_platform_object)) {			
					collided++;
					if (!is_undefined(list)) { // Add to List
						ds_list_add(list, side_platform_object.id);
					} else {
						break;
					}
				}	
			}
		}
		ds_list_clear(global.MyCollisionList);
		if (collided > 0) {	
			return (collided);
		}		
	}	
	return 0;
}
/// @desc With this function you can check a place for platform collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject|Id.Instance} [obj] The object to check for. (Optional)
/// @returns {bool}
function place_meeting_platform(xx, yy, obj = obj_platform) {
	return (instance_place_list_platform(xx, yy, obj) > 0);
}
/// @desc With this function you can check a position for platform collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject|Id.Instance} [obj] The object to check for. (Optional)
/// @returns {bool}
function position_meeting_platform(xx, yy, obj = obj_platform) {
	var old_mask = mask_index;
	mask_index = spr_unownPixel;
	var check_collision = (instance_place_list_platform(xx, yy, obj) > 0);
	mask_index = old_mask;
	return check_collision;
}	
/// @desc With this function you can check a place for side platform collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject|Id.Instance} [obj] The object to check for. (Optional)
/// @returns {bool}
function place_meeting_sidePlatform(xx, yy, obj = obj_sidePlatform) {
	return (instance_place_list_sidePlatform(xx, yy, obj) > 0);
}
/// @desc With this function you can check a position for side platform collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject|Id.Instance} [obj] The object to check for. (Optional)
/// @returns {bool}
function position_meeting_sidePlatform(xx, yy, obj = obj_sidePlatform) {
	var old_mask = mask_index;
	mask_index = spr_unownPixel;
	var check_collision = (instance_place_list_sidePlatform(xx, yy, obj) > 0);
	mask_index = old_mask;
	return check_collision;
}		
#endregion

#region Moving Platforms
/// @desc With this function you can check a place for moving platform collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject|Id.Instance} [obj] The object to check for. (Optional)
/// @param {ID.DsList} [list] The DS list to use to store the IDs of colliding moving platforms. (Optional)
/// @returns {real} The number of instances found to be in collision.
function instance_place_list_movingPlatform(xx, yy, obj = obj_movingPlatform, list = undefined) {
	var collided = 0;
	if (place_meeting(xx, yy, obj)) { // Basic moving Platforms		
		var movingplatform_number = instance_place_list(xx, yy, obj, global.MyCollisionList, false);
		if (movingplatform_number > 0) {
			for (var i = 0; i < movingplatform_number; ++i;) {
				var movingplatform_object = (global.MyCollisionList[| i]);
				
				var _can_collide = true;
				if (variable_instance_exists(movingplatform_object, "canCollide")) {
					_can_collide = movingplatform_object.canCollide(object_index);
				}
				var _check = (sign(movingplatform_object.image_yscale) <= -1 ? yy <= y : yy > y);			
				if (_check == true && _can_collide && place_meeting(xx, yy, movingplatform_object) && !place_meeting(xx, y, movingplatform_object)) {			
					collided++;
					if (!is_undefined(list)) { // Add to List
						ds_list_add(list, movingplatform_object.id);
					} else {
						break;
					}
				}	
			}
		}
		ds_list_clear(global.MyCollisionList);
		if (collided > 0) {	
			return (collided);
		}		
	}	
	return 0;
}
/// @desc With this function you can check a place for moving platform collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject|Id.Instance} [obj] The object to check for. (Optional)
/// @returns {bool}
function place_meeting_movingPlatform(xx, yy, obj = obj_movingPlatform) {
	return (instance_place_list_movingPlatform(xx, yy, obj) > 0);
}
/// @desc With this function you can check a position for moving platform collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject|Id.Instance} [obj] The object to check for. (Optional)
/// @returns {bool}
function position_meeting_movingPlatform(xx, yy, obj = obj_movingPlatform) {
	var old_mask = mask_index;
	mask_index = spr_unownPixel;
	var check_collision = (instance_place_list_movingPlatform(xx, yy, obj) > 0);
	mask_index = old_mask;
	return check_collision;
}		
#endregion

#region Sloped Platforms
/// @desc With this function you can check a place for sloped platform collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject|Id.Instance} [obj] The object to check for. (Optional)
/// @param {ID.DsList} [list] The DS list to use to store the IDs of colliding sloped platforms. (Optional)
/// @returns {real} The number of instances found to be in collision.
function instance_place_list_slopePlatform(xx, yy, obj = obj_slopePlatform, list = undefined) {
	var old_x = x;
	var old_y = y;
	var old_bbox_top = bbox_top;
	var old_bbox_bottom = bbox_bottom;	
	x = xx;
	y = yy;
	
	var collided = 0;
	if (place_meeting(x, y, obj)) { // Basic sloped Platforms		
		var slopeplatform_number = instance_place_list(x, y, obj, global.MyCollisionList, false);
		if (slopeplatform_number > 0) {
			for (var i = 0; i < slopeplatform_number; ++i;) {
				var slopeplatform_object = (global.MyCollisionList[| i]);
				
				var _can_collide = true;
				if (variable_instance_exists(slopeplatform_object, "canCollide")) {
					_can_collide = slopeplatform_object.canCollide(object_index);
				}
				
				if (_can_collide) {			
					#region Checks
					var object_side =  slopeplatform_object.image_xscale > 0 ? bbox_right : bbox_left;
					object_side = (object_side - x) + old_x;
					
					var player_pos = point_direction(slopeplatform_object.x + slopeplatform_object.sprite_width, slopeplatform_object.y + slopeplatform_object.sprite_height, x, y);
					
					
					var _check1;
					if (slopeplatform_object.image_yscale > 0) {
						_check1 = slopeplatform_object.image_xscale > 0 ? (player_pos <= 180 && player_pos >= 90) : (player_pos <= 90 && player_pos >= 0);
					} else {
						_check1 = slopeplatform_object.image_xscale > 0 ? (player_pos <= 270 && player_pos >= 180) : ((player_pos <= 360 || player_pos <= 0) && player_pos >= 270);
					}
					
					var _check2 = !triangle_meeting(old_x, old_y, slopeplatform_object.x, slopeplatform_object.y + slopeplatform_object.sprite_height, slopeplatform_object.x + slopeplatform_object.sprite_width, slopeplatform_object.y, slopeplatform_object.x + slopeplatform_object.sprite_width, slopeplatform_object.y + slopeplatform_object.sprite_height);
					var _check3 = (slopeplatform_object.image_xscale > 0 ? object_side <= slopeplatform_object.bbox_left : object_side >= slopeplatform_object.bbox_right);
					#endregion
					if (_check1 && (_check2 || _check3) && (slopeplatform_object.image_yscale > 0 ? old_bbox_bottom <= slopeplatform_object.bbox_bottom : old_bbox_top >= slopeplatform_object.bbox_top) && triangle_meeting(x, y, slopeplatform_object.x, slopeplatform_object.y + slopeplatform_object.sprite_height, slopeplatform_object.x + slopeplatform_object.sprite_width, slopeplatform_object.y, slopeplatform_object.x + slopeplatform_object.sprite_width, slopeplatform_object.y + slopeplatform_object.sprite_height)) {
						collided++;
						if (!is_undefined(list)) { // Add to List
							ds_list_add(list, slopeplatform_object.id);
						} else {
							break;
						}
					}						

				}	
			}
		}
		ds_list_clear(global.MyCollisionList);
		if (collided > 0) {	
			x = old_x;
			y = old_y;			
			return (collided);
		}		
	}	
	x = old_x;
	y = old_y;	
	return 0;
}
/// @desc With this function you can check a place for sloped platform collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject|Id.Instance} [obj] The object to check for. (Optional)
/// @returns {bool}
function place_meeting_slopePlatform(xx, yy, obj = obj_slopePlatform) {
	return (instance_place_list_slopePlatform(xx, yy, obj) > 0);
}
/// @desc With this function you can check a position for sloped platform collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject|Id.Instance} [obj] The object to check for. (Optional)
/// @returns {bool}
function position_meeting_slopePlatform(xx, yy, obj = obj_slopePlatform) {
	var old_mask = mask_index;
	mask_index = spr_unownPixel;
	var check_collision = (instance_place_list_slopePlatform(xx, yy, obj) > 0);
	mask_index = old_mask;
	return check_collision;
}		
#endregion

#region Slopes
/// @desc With this function you can check a place for slope collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject*}{Id.Instance*} [obj] The object to check for. (Optional)
/// @param {ID.DsList} [list] The DS list to use to store the IDs of colliding slopes. (Optional)
/// @returns {real} The number of instances found to be in collision.
function instance_place_list_slope(xx, yy, obj = obj_slope, list = undefined) {
	if (place_meeting(xx, yy, obj)) { // Basic slopes		
		var slope_number = instance_place_list(xx, yy, obj, global.MyCollisionList, false);
		var collided = 0;
		if (slope_number > 0) {
			for (var i = 0; i < slope_number; ++i;) {
				var slope_object = (global.MyCollisionList[| i]);
				
				var _can_collide = true;
				if (variable_instance_exists(slope_object, "canCollide")) {
					_can_collide = slope_object.canCollide(object_index);
				}
				
				if (_can_collide == true && triangle_meeting(xx, yy, slope_object.x, slope_object.y + slope_object.sprite_height, slope_object.x + slope_object.sprite_width, slope_object.y, slope_object.x + slope_object.sprite_width, slope_object.y + slope_object.sprite_height)) {				
					collided++;
					if (!is_undefined(list)) { // Add to List
						ds_list_add(list, slope_object.id);
					} else {
						break;
					}
				}	
			}
		}
		ds_list_clear(global.MyCollisionList);
		if (collided > 0) {	
			return (collided);
		}		
	}	
	return 0;
}
/// @desc With this function you can check a place for slope collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {bool} [check_slopePlatform] Toggle to check for Sloped Platforms.
/// @param {Asset.GMObject*}{Id.Instance*} [obj] The object to check for. (Optional)
/// @returns {bool}
function place_meeting_slope(xx, yy, check_slopePlatform = true, obj = obj_slope) {
	var _check2 = (check_slopePlatform ? place_meeting_slopePlatform(xx, yy) : false);
	return (instance_place_list_slope(xx, yy, obj) > 0 || _check2);
}
/// @desc With this function you can check a position for slope collision objects.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject*}{Id.Instance*} [obj] The object to check for. (Optional)
/// @returns {bool}
function position_meeting_slope(xx, yy, obj = obj_slope) {
	var old_mask = mask_index;
	mask_index = spr_unownPixel;
	var check_collision = (instance_place_list_slope(xx, yy, obj) > 0);
	mask_index = old_mask;
	return check_collision;
}		



/// @desc With this function you can check a place for a collision with slope's backside.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject*}{Id.Instance*} [obj] The object to check for. (Optional)
/// @param {ID.DsList} [list] The DS list to use to store the IDs of colliding slopes. (Optional)
/// @returns {real} The number of instances found to be in collision.
function instance_place_list_slopeSolid(xx, yy, obj = obj_slope, list = undefined) {
	if (place_meeting(xx, yy, obj)) { // Basic slopes		
		var slope_number = instance_place_list(xx, yy, obj, global.MyCollisionList, false);
		var collided = 0;
		if (slope_number > 0) {
			for (var i = 0; i < slope_number; ++i;) {
				var slope_object = (global.MyCollisionList[| i]);
				
				var _can_collide = true;
				if (variable_instance_exists(slope_object, "canCollide")) {
					_can_collide = slope_object.canCollide(object_index);
				}
				var _xscale = (xx - x);
				var _check1 = (sign(slope_object.image_xscale) != _xscale && _xscale != 0)
				var _check2 = (slope_object.image_yscale < 0 ? bbox_bottom <= slope_object.bbox_top : bbox_top >= slope_object.bbox_bottom);
				
				if (_can_collide == true && (_check1 || _check2) && triangle_meeting(xx, yy, slope_object.x, slope_object.y + slope_object.sprite_height, slope_object.x + slope_object.sprite_width, slope_object.y, slope_object.x + slope_object.sprite_width, slope_object.y + slope_object.sprite_height)) {				
					collided++;
					if (!is_undefined(list)) { // Add to List
						ds_list_add(list, slope_object.id);
					} else {
						break;
					}
				}	
			}
		}
		ds_list_clear(global.MyCollisionList);
		if (collided > 0) {	
			return (collided);
		}			
	}	
	return 0;
}
/// @desc With this function you can check a place for a collision with slope's backside.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject*}{Id.Instance*} [obj] The object to check for. (Optional)
/// @returns {bool}
function place_meeting_slopeSolid(xx, yy, obj = obj_slope) {
	return (instance_place_list_slopeSolid(xx, yy, obj) > 0);
}
/// @desc With this function you can check a position for a collision with slope's backside.
/// @param {any*} x The x position to check.
/// @param {any*} y The y position to check.
/// @param {Asset.GMObject*}{Id.Instance*} [obj] The object to check for. (Optional)
/// @returns {bool}
function position_meeting_slopeSolid(xx, yy, obj = obj_slope) {
	var old_mask = mask_index;
	mask_index = spr_unownPixel;
	var check_collision = (instance_place_list_slopeSolid(xx, yy, obj) > 0);
	mask_index = old_mask;
	return check_collision;
}		
#endregion