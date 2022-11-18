#pragma once

#include "Color.h"

struct Vertex {
	float x, y, z;
	Color c;
	float tex_coords_x, tex_coords_y;
	float tex_id;
	float tiling_factor;
};

struct PostRenderingVertex {
	float x, y, z;
	float tex_coords_x, tex_coords_y;
};

