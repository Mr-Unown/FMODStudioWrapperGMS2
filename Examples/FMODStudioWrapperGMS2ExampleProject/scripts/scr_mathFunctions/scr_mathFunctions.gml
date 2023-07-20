/// @description Approach the value towards target provided.
/// @param value The value to be changed.
/// @param target The value targetted.
/// @param amount The amount to change.
function approach(value, target, amount) {
	return value + clamp(target - value, -abs(amount), abs(amount));
}

/// @description Returns the value wrapped to the range [min, max] (min and max can be swapped).
/// @function wrap
/// @param value The value to wrap into the bounds
/// @param min Minimum bound, inclusive
/// @param max Maximum bound, inclusive
function wrap(value, minb, maxb) {
	value = floor(value);
	var _min = floor(min(minb, maxb));
	var _max = floor(max(minb, maxb));
	var range = _max - _min + 1; // + 1 is because max bound is inclusive
	return (((value - _min) % range) + range) % range + _min;
}

/// @description Returns true or false depending on RNG.
/// @param percent 
function chance(percent) {
	return percent > random(1);
}

/// @description Returns a value that will wave back and forth between [from-to] over [duration] seconds
/// @param from 	
/// @param to
/// @param duration
/// @param offset
function wave(from, to, duration, offset) {
	var a4 = (to - from) * 0.5;
	return from + a4 + sin((((current_time * 0.001) + duration * offset) / duration) * (pi * 2)) * a4;	
}
