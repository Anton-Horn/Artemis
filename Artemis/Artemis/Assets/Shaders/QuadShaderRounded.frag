

#version 450
layout(location = 0) out vec4 o_Color;

in vec4 v_color;
in vec3 v_position;

in vec2 v_uv;

uniform float u_radius;
uniform vec2 u_size;

float roundedBoxSDF(vec2 CenterPosition, vec2 Size, float Radius) {
    return length(max(abs(CenterPosition)-Size+Radius,0.0)) - Radius;
}

void main() 
{
	float dist = roundedBoxSDF(v_position.xy, u_size / 2.0f, u_radius);
	vec3 color = vec3(1.0f - (dist / fwidth(dist)));
	o_Color = vec4(v_color.rgb * color, color.r);
};