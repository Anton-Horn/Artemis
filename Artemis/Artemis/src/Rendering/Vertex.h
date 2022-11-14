#pragma once

#include "Color.h"


	
struct Vertex {
	float x, y, z;
	Color c;
	float TexCoordsX, TexCoordsY;
	float TexID;
	float TilingFactor;
};

struct PostRenderingVertex {
	float x, y, z;
	float TexCoordsX, TexCoordsY;
};

