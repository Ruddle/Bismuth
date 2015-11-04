#version 330

in vec2 UV;
out vec4 outColor;

uniform sampler2D gNormal;
uniform sampler2D gDiffuse;
uniform sampler2D gPosition;
uniform sampler2D aoSampler;
uniform mat4 view;
uniform float time;
uniform vec2 resolution;
uniform float aspect;
uniform float tanHalfFov;
uniform float near;
uniform float far;
uniform bool keyF1;
uniform bool keyF2;
uniform bool keyF3;
uniform bool keyF4;
uniform bool keyF5;
uniform bool keyF6;
uniform bool keyF7;
uniform bool keyF8;



struct Light
{
  vec3 position_WorldSpace;
  vec3 intensity;
};

const Light lights[2] = Light[2](  Light(vec3(10,-2,10),vec3(1,0.9,0.8))  ,   Light(vec3(-10,-2,10),vec3(0.8,0.9,1))  );

void main()
{

vec3 lighting= vec3(0);

vec3 position_ViewSpace ;
	position_ViewSpace.z = -texture(gPosition, UV).r ;
	position_ViewSpace.x = -(UV.x*2-1)*position_ViewSpace.z*(aspect) *tanHalfFov ;
	position_ViewSpace.y = -(UV.y*2-1)*position_ViewSpace.z *tanHalfFov ;

vec3 normal = vec3(texture(gNormal, UV).rg,0);
    normal.z= sqrt(1.0 - normal.x*normal.x - normal.y*normal.y); 

vec3 diffuse = texture(gDiffuse, UV).xyz;
float ao = texture(aoSampler,UV).x;

for(int k=0;k<2;k++){
	vec3 i = position_ViewSpace- (view* vec4(lights[k].position_WorldSpace,1)).xyz;
	float dist = length(i) *length(i);
	i=normalize(i);
	float alpha = dot(-i,normal);
	alpha = clamp(alpha,0,1);
	float attenuation = 1/(1+    pow( dist/300.0,2)    );
	
	lighting += (attenuation+0.2) * (alpha+0.2)*diffuse*lights[k].intensity;
}
if(!keyF4) lighting=lighting*(ao*1.0);


if(keyF1) lighting = normal;
if(keyF2) lighting = position_ViewSpace*vec3(1,1,-1);
if(keyF3) lighting = vec3(ao);



outColor =		vec4(lighting,1);


}
