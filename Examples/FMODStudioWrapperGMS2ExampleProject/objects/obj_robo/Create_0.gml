enum States {
	Normal,
	Crouch,
	Flying,
}

scr_collision_init();
terminalVelocity = 7;
grav = 0.25;

xscale = 1;
state = States.Normal;
dispensed = false;
stepped = false

bgm = fmod_createEventInstance("event:/BGM/BGM")
fmod_event_play(bgm)
metalclanksnd = fmod_createEventInstance("event:/SFX/MetalClank")
dispensesnd = fmod_createEventInstance("event:/SFX/BombDispense")

depth = -10