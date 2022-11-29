#pragma once

#include "Color.h"

struct Vertex {
	float x, y, z;
	Color c;
	float uv_x, uv_y;
};

struct PostRenderingVertex {
	float x, y, z;
	float tex_coords_x, tex_coords_y;
};

