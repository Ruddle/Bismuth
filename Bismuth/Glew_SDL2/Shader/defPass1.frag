#version 330

in vec2 UV;
in vec3 varNormal;
in vec3 varBitangent;
in vec3 varTangent;

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
//	vec3 B = normalize(varBitangent);
	vec3 T = normalize(varTangent);
	vec3 texture_n = normalize(texture(texture_normal, UV).xyz*2.0-1.0);

	T = normalize(T - dot(T, gNormal) * gNormal);
	vec3 B = cross(T, gNormal);

	mat3 TBN = mat3(T,B,gNormal);

	gNormal = normalize(TBN*texture_n +1*varNormal );

	//TEST ENCODAGE
	float p = sqrt(gNormal.z*8+8);
    gNormal = vec3(gNormal.xy/p,0);
	//TEST ENCODAGE FIN
	gNormal.z = texture(texture_emit, UV).x;
	gPosition = -varPosition.z;

	vec2 a = (varCurrPosition_Proj.xy / varCurrPosition_Proj.w) * 0.5 + 0.5;
    vec2 b = (varPrevPosition_Proj.xy / varPrevPosition_Proj.w) * 0.5 + 0.5;
  
	gSpeed =   max(abs(a-b)-vec2(0.005),vec2(0)) ;
}
