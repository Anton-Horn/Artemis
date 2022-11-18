#version 450
layout(location = 0) out vec4 color;

in vec4 v_color;
in vec2 v_TexCoords;
in float v_TexIndex;
in float v_TilingFactor;

uniform sampler2D u_Samplers[32];

void main() 
{
	vec4 TexColor;
	switch(int(v_TexIndex)) 
	{
		case 0: TexColor = texture(u_Samplers[0], v_TexCoords * v_TilingFactor);break;
		case 1: TexColor = texture(u_Samplers[1], v_TexCoords * v_TilingFactor);break;
		case 2: TexColor = texture(u_Samplers[2], v_TexCoords * v_TilingFactor);break;
		case 3: TexColor = texture(u_Samplers[3], v_TexCoords * v_TilingFactor);break;
		case 4: TexColor = texture(u_Samplers[4], v_TexCoords * v_TilingFactor);break;
		case 5: TexColor = texture(u_Samplers[5], v_TexCoords * v_TilingFactor);break;
		case 6: TexColor = texture(u_Samplers[6], v_TexCoords * v_TilingFactor);break;
		case 7: TexColor = texture(u_Samplers[7], v_TexCoords * v_TilingFactor);break;
		case 8: TexColor = texture(u_Samplers[8], v_TexCoords * v_TilingFactor);break;
		case 9: TexColor = texture(u_Samplers[9], v_TexCoords * v_TilingFactor);break;
		case 10: TexColor = texture(u_Samplers[10], v_TexCoords * v_TilingFactor);break;
		case 11: TexColor = texture(u_Samplers[11], v_TexCoords * v_TilingFactor);break;
		case 12: TexColor = texture(u_Samplers[12], v_TexCoords * v_TilingFactor);break;
		case 13: TexColor = texture(u_Samplers[13], v_TexCoords * v_TilingFactor);break;
		case 14: TexColor = texture(u_Samplers[14], v_TexCoords * v_TilingFactor);break;
		case 15: TexColor = texture(u_Samplers[15], v_TexCoords * v_TilingFactor);break;
		case 16: TexColor = texture(u_Samplers[16], v_TexCoords * v_TilingFactor);break;
		case 17: TexColor = texture(u_Samplers[17], v_TexCoords * v_TilingFactor);break;
		case 18: TexColor = texture(u_Samplers[18], v_TexCoords * v_TilingFactor);break;
		case 19: TexColor = texture(u_Samplers[19], v_TexCoords * v_TilingFactor);break;
		case 20: TexColor = texture(u_Samplers[20], v_TexCoords * v_TilingFactor);break;
		case 21: TexColor = texture(u_Samplers[21], v_TexCoords * v_TilingFactor);break;
		case 22: TexColor = texture(u_Samplers[22], v_TexCoords * v_TilingFactor);break;
		case 23: TexColor = texture(u_Samplers[23], v_TexCoords * v_TilingFactor);break;
		case 24: TexColor = texture(u_Samplers[24], v_TexCoords * v_TilingFactor);break;
		case 25: TexColor = texture(u_Samplers[25], v_TexCoords * v_TilingFactor);break;
		case 26: TexColor = texture(u_Samplers[26], v_TexCoords * v_TilingFactor);break;
		case 27: TexColor = texture(u_Samplers[27], v_TexCoords * v_TilingFactor);break;
		case 28: TexColor = texture(u_Samplers[28], v_TexCoords * v_TilingFactor);break;
		case 29: TexColor = texture(u_Samplers[29], v_TexCoords * v_TilingFactor);break;
		case 30: TexColor = texture(u_Samplers[30], v_TexCoords * v_TilingFactor);break;
		case 31: TexColor = texture(u_Samplers[31], v_TexCoords * v_TilingFactor);break;
	}
	
	color = TexColor * v_color;
};