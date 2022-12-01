#version 450
layout(location = 0) out vec4 o_Color;

in vec4 v_color;
in vec3 v_position;
in vec2 v_uv;

void main() 
{
 	vec2 position = v_uv * 2.0f - 1.0f;
	float distance = 1.0 - length(position);
	vec3 color = vec3(distance / fwidth(distance));
	o_Color = vec4(color * v_color.rgb, color.r);
};