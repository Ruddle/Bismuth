#version 330

in vec2 varUV;
in vec3 varNormal;

uniform sampler2D texture_diffuse;

layout (location = 0) out vec3 gNormal;


void main()
{
	gNormal =  texture(texture_diffuse, varUV).xyz;
}
