#version 450
layout(location = 0) out vec4 color;

in vec2 TexCoords;

uniform sampler2D u_sampler;

void main()
{ 
   color = texture(u_sampler, TexCoords);	
}