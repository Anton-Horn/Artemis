#version 450
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_uv;

out vec4 v_color;
out vec3 v_position;
out vec2 v_uv;

uniform mat4 u_projection_matrix;

void main() 
{
	
	v_color = a_color;
	v_position = a_position;
	v_uv = a_uv;
	gl_Position = u_projection_matrix * vec4(a_position.x, a_position.y, a_position.z, 1.0f);
}