#version 330

in vec2 varUV;
in vec3 varNormal;
in vec3 varPosition;

uniform sampler2D texture_diffuse;
uniform vec2 resolution;

layout (location = 0) out vec2 gNormal;
layout (location = 1) out vec4 gDiffuse;
layout (location = 2) out float gPosition;


void main()
{
	gDiffuse= vec4(texture(texture_diffuse, varUV).xyz,1.0);
	gNormal =  varNormal.xy;
	gPosition = -varPosition.z;
}
