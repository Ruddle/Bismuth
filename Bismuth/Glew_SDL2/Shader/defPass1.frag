#version 330

in vec2 varUV;
in vec3 varNormal;
in vec3 varPosition;

uniform sampler2D texture_diffuse;
uniform vec2 resolution;

layout (location = 0) out vec2 gNormal;
layout (location = 1) out vec4 gDiffuse;
layout (location = 2) out vec4 gPosition;


const float NEAR = 0.010f; // projection matrix's near plane
const float FAR = 100.0f; // projection matrix's far plane
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * NEAR * FAR) / (FAR + NEAR - z * (FAR - NEAR));	
}


void main()
{
	gDiffuse= vec4(texture(texture_diffuse, varUV).xyz,1.0);
	gNormal =  varNormal.xy;
	gPosition.xyz = varPosition;
	gPosition.a = LinearizeDepth(gl_FragCoord.z);
}
