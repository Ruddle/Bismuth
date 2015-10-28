#version 330

in vec2 varUV;
in vec3 varNormal;

uniform sampler2D texture_diffuse;

layout (location = 0) out vec3 gNormal;
layout (location = 1) out vec3 gDiffuse;
layout (location = 2) out vec3 gPosition;

void main()
{
	gDiffuse= texture(texture_diffuse, varUV).xyz;
	gNormal =  varNormal;
	gPosition = gl_FragCoord.xyz;
}
