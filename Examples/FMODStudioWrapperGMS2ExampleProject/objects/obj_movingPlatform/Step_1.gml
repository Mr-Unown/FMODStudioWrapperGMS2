/// @description Moving Platform Movement.
// Moving Code
hsp = lengthdir_x(moveSpeed - stopSpeed, targetDirection);
vsp = lengthdir_y(moveSpeed - stopSpeed, targetDirection);
trueX += hsp;
trueY += vsp;
x = round(trueX);
y = round(trueY);

// Collide and interact with Triggers
if (place_meeting(x + sign(hsp), y + sign(vsp), obj_movingPlatformTrigger) && stopped = false) {
	with (instance_place(x + sign(hsp), y + sign(vsp), obj_movingPlatformTrigger)) {
		if (other.stopid != id) {
			other.platformDirection = targetAngle;
			other.stopped = true;
			other.stopid = id;
		}
	}
}
// Smooth in and out
if (stopped == true) {
	stopSpeed = approach(stopSpeed, stopSpeedMax, stopSpeedAcc);
	if (stopSpeed >= stopSpeedMax) {
		targetDirection = platformDirection;
		stopped = false;
	}
}
else {
	stopSpeed = approach(stopSpeed, 0, stopSpeedDecc);
}



