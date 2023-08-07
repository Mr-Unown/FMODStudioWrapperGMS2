/// @desc Plays an event. Only for one-and-done events.
/// @param {string} event_path Relative path to the FMOD Event.
/// @returns {real} event_handle Returns a handle to the FMOD Event Instance Object.
function event_play_oneshot(event_path) {
	var event_id = fmod_createEventInstance(event_path);
	fmod_event_play(event_id);
	fmod_event_release(event_id);
	return event_id;
}

/// @desc Check if any instance of the event is playing.
/// @param {real} event_handle Handle to the FMOD Event Instance Object.
function event_isplaying(event_handle) {
	return (fmod_event_getPlaybackState(event_handle) == FMOD_STUDIO_PLAYBACK_PLAYING);
}
