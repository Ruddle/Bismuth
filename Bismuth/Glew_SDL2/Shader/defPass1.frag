#version 330

in vec2 UV;
in vec3 varNormal;
in vec3 varPosition;
in vec4 varPrevPosition_Proj;
in vec4 varCurrPosition_Proj;
uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
uniform sampler2D texture_spec;
uniform sampler2D texture_emit;
uniform vec2 resolution;

layout (location = 0) out vec3 gNormal;
layout (location = 1) out vec4 gDiffuse;
layout (location = 2) out float gPosition;
layout (location = 3) out vec2 gSpeed;



void main()
{
	gDiffuse= vec4(texture(texture_diffuse, UV).xyz,   texture(texture_spec, UV).x        );

	gNormal    =  normalize(varNormal);
	

	gNormal.z = texture(texture_emit, UV).x;
	gPosition = -varPosition.z;

	vec2 a = (varCurrPosition_Proj.xy / varCurrPosition_Proj.w) * 0.5 + 0.5;
    vec2 b = (varPrevPosition_Proj.xy / varPrevPosition_Proj.w) * 0.5 + 0.5;
  
	gSpeed =   max(abs(a-b)-vec2(0.005),vec2(0)) ;
}
