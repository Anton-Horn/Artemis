#version 450
layout(location = 0) out vec4 o_Color;

in vec4 v_color;
in vec3 v_position;
in vec2 v_uv;

uniform sampler2D u_char_texture;

void main() 
{
	vec4 sampled_color = vec4(1.0f,1.0f, 1.0f, texture(u_char_texture, v_uv).r)
	o_Color = vec4(v_color.rgb, 1.0f) * sampled_color;
};