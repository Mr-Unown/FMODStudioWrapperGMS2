repeat(5) {
	with(instance_create_depth(x + 8, y + 8, depth, obj_debris))
		image_blend = other.image_blend;
}