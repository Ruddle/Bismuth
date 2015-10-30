#version 330

in vec2 varUV;
in vec3 varNormal;
in vec3 varPosition;

uniform sampler2D texture_diffuse;

layout (location = 0) out vec3 gNormal;
layout (location = 1) out vec3 gDiffuse;
layout (location = 2) out vec4 gPosition;

void main()
{
	gDiffuse= texture(texture_diffuse, varUV).xyz;
	gNormal =  varNormal;
	gPosition.xyz = varPosition;
	gPosition.a = gl_FragCoord.z;
}
