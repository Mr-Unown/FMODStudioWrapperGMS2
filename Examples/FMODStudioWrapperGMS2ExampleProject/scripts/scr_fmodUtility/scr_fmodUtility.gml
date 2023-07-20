/// @desc Plays an event. Only for one-and-done events.
/// @param {string} event_path Relative path to the FMOD Event.
/// @returns {real} event_handle Returns a handle to the FMOD Event Instance Object.
function event_play_oneshot(event_path) {
	var _id = fmod_createEventInstance(event_path);
	fmod_event_play(_id);
	fmod_event_release(_id);
	return _id;
}
/// @desc Check if any instance of the event is playing.
/// @param {string} event_path Relative path to the FMOD Event.
function event_isplaying(event_path) {
	return (fmod_event_getPlaybackState(event_path) == FMOD_STUDIO_PLAYBACK_PLAYING);
}