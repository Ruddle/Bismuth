#version 330

in vec2 UV;
out vec4 outColor;

uniform sampler2D gNormal;
uniform sampler2D gDiffuse;
uniform sampler2D gPosition;
uniform vec2 resolution;

struct Light
{
  vec3 position_ViewSpace;
  vec3 intensity;
};

const Light lights[2] = Light[2](  Light(vec3(10,0,0),vec3(1,0.9,0.8))  ,   Light(vec3(-10,0,0),vec3(0.8,0.9,1))  );

void main()
{

vec3 lighting= vec3(0);

vec3 position = texture(gPosition, vec2(0,0)+UV*2).xyz;
vec3 normal   = texture(gNormal, vec2(0,0)+UV*2).xyz;
vec3 diffuse = texture(gDiffuse, vec2(0,0)+UV*2).xyz;

for(int k=0;k<2;k++){
	vec3 i = position-lights[k].position_ViewSpace;
	float dist = length(i) *length(i);
	i=normalize(i);
	float alpha = dot(-i,normal);
	alpha = clamp(alpha,0,1);
	float attenuation = (1/(dist/50000));
	attenuation=1;
	lighting += attenuation* (alpha+0.2)*diffuse*lights[k].intensity;
}

if(gl_FragCoord.x>resolution.x/2.0 ||gl_FragCoord.y>resolution.y/2.0)
lighting=vec3(0);

vec4 diffuseSide = (gl_FragCoord.x<resolution.x/2.0 && gl_FragCoord.y>resolution.y/2.0) ? texture(gDiffuse, vec2(0,-1)+UV*2) : vec4(0);
vec4 normalSide = (gl_FragCoord.x>resolution.x/2.0 && gl_FragCoord.y>resolution.y/2.0) ? texture(gNormal, vec2(-1,-1)+UV*2) : vec4(0);
vec4 positionSide = (gl_FragCoord.x>resolution.x/2.0 && gl_FragCoord.y<resolution.y/2.0) ? vec4(texture(gPosition, vec2(-1,0)+UV*2).xyz*vec3(1,1,-0.1),1) : vec4(0);

outColor =		diffuseSide + 
				normalSide + 	 
			    positionSide +
				vec4(lighting,1);
}
