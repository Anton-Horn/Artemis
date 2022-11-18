#version 450
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texCoords;
layout(location = 3) in float a_texIndex;
layout(location = 4) in float a_TilingFactor;

out vec4 v_color;
out vec2 v_TexCoords;
out float v_TexIndex;
out float v_TilingFactor;

uniform mat4 u_ProjectionMatrix;

void main() 
{
	v_color = a_color;
	v_TexCoords = a_texCoords;
	v_TexIndex = a_texIndex;
	v_TilingFactor = a_TilingFactor;
	gl_Position = u_ProjectionMatrix * vec4(a_position, 1.0f);
}