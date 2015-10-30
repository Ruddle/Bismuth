#version 330

in vec2 UV;
out vec4 outColor;

uniform sampler2D gNormal;
uniform sampler2D gDiffuse;
uniform sampler2D gPosition;

const vec3 lightPosition_ViewSpace[2] = vec3[2]( vec3(800+800,450+450,-100) , vec3(800-800,450-450,-100)  );

struct Light
{
  vec3 position_ViewSpace;
  vec3 intensity;
};

//const Light lights[2] = Light[2](  Light(vec3(800+800,450+450,-100),vec3(1,1,0.9))  ,   Light(vec3(800-800,450-450,-100),vec3(0.98,0.98,1))  );
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

if(gl_FragCoord.x>800 ||gl_FragCoord.y>450)
lighting=vec3(0);


outColor =		texture(gDiffuse, vec2(0,-1)+UV*2) + 
				texture(gNormal, vec2(-1,-1)+UV*2) + 	 
			    vec4(texture(gPosition, vec2(-1,0)+UV*2).xyz*vec3(1,1,-0.1),1) +
				vec4(lighting,1);
}
