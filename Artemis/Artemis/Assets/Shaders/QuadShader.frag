#version 450
layout(location = 0) out vec4 o_Color;

in vec4 v_color;
in vec3 v_position;
in vec2 v_uv;

void main() 
{
	o_Color = v_color;
};