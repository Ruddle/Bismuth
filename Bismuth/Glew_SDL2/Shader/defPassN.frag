#version 330

in vec2 UV;
out vec4 outColor;

uniform sampler2D gNormal;
uniform sampler2D gDiffuse;
uniform sampler2D gPosition;
uniform sampler2D aoSampler;
uniform float time;
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

vec3 position = texture(gPosition, UV).xyz;

vec3 normal = vec3(texture(gNormal, UV).rg,0);
    normal.z= sqrt(1.0 - normal.x*normal.x - normal.y*normal.y); 

vec3 diffuse = texture(gDiffuse, UV).xyz;
float ao = texture(aoSampler,UV).x;

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

    // Retrieve data from gbuffer
    vec3 FragPos ;
	float depth = texture(gPosition, UV).a;



	float widthInv = 1.0/1200.0;
	float heightInv = 1.0/700.0;
	float aspectInv = 7.0/12.0;
	float fov= 70*3.14159265359/180.0;

	FragPos.x = (UV.x*2-1)*fov*depth;
	FragPos.y = (UV.y*2-1)*fov*depth*aspectInv*1.019;
	FragPos.z = 0.1*depth ;


//lighting  = vec3(ao) ;


outColor =		vec4(lighting*(ao+0.3),1);

}
