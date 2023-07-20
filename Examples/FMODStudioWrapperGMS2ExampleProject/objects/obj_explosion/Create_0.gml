explosionsnd = fmod_createEventInstance("event:/SFX/Explosion");
event_play_at(explosionsnd, x, y);
obj_camera.shake += 5;