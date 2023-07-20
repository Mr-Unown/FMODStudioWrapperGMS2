/// @desc Returns true if object collision collides with a given triangle
/// @param  {real} sx The x position to check for.
/// @param  {real} sy The y position to check for.
/// @param  {real} x1 x-coordinate of 1st point of triangle.
/// @param  {real} y1 y-coordinate of 1st point of triangle.
/// @param  {real} x2 x-coordinate of 2nd point of triangle.
/// @param  {real} y2 y-coordinate of 2nd point of triangle.
/// @param  {real} x3 x-coordinate of 3rd point of triangle.
/// @param  {real} y3 y-coordinate of 3rd point of triangle.
/// @returns {bool}

function triangle_meeting(sx, sy, x1, y1, x2, y2, x3, y3)
{
	var old_x = x;
	var old_y = y;
	x = sx;
	y = sy;

	if rectangle_in_triangle(bbox_left, bbox_top, bbox_right, bbox_bottom, x1, y1, x2, y2, x3, y3) > 0 {
		x = old_x;
		y = old_y;
		return true;	
	}
	x = old_x;
	y = old_y;	
	return false;
}

function unown_absfloor(a) {
	return (a > 0 ? floor(a) : ceil(a))
}