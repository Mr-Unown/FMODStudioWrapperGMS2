bombtickingsnd = fmod_createEventInstance("event:/SFX/BombTick")
metalclanksnd = fmod_createEventInstance("event:/SFX/MetalClank")
fmod_event_play(bombtickingsnd)
scr_collision_init();
terminalVelocity = 7;
grav = 0.25;
timer = 160;