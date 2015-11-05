#version 330

in vec2 UV;
out vec4 outColor;

uniform sampler2D gNormal;
uniform sampler2D gDiffuse;
uniform sampler2D gPosition;
uniform sampler2D aoSampler;
uniform sampler2D bloomSampler;
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

const Light lights[2] = Light[2](  Light(vec3(10,-4,10),vec3(1,0.9,0.8))  ,   Light(vec3(-10,-4,10),vec3(0.8,0.9,1))  );



float Cook_Torrance(vec3 lightDirection, vec3 eyeDir, vec3 normal, float roughnessValue , float F0){


 float NdotL = max(dot(normal, lightDirection), 0.0);
    
    float specular = 0.0;
    if(NdotL > 0.0)
    {
        // calculate intermediary values
        vec3 halfVector = normalize(lightDirection + eyeDir);
        float NdotH = max(dot(normal, halfVector), 0.0); 
        float NdotV = max(dot(normal, eyeDir), 0.0); // note: this could also be NdotL, which is the same value
        float VdotH = max(dot(eyeDir, halfVector), 0.0);
        float mSquared = roughnessValue * roughnessValue;
        
        // geometric attenuation
        float NH2 = 2.0 * NdotH;
        float g1 = (NH2 * NdotV) / VdotH;
        float g2 = (NH2 * NdotL) / VdotH;
        float geoAtt = min(1.0, min(g1, g2));
     
        // roughness (or: microfacet distribution function)
        // beckmann distribution function
        float r1 = 1.0 / ( 4.0 * mSquared * pow(NdotH, 4.0));
        float r2 = (NdotH * NdotH - 1.0) / (mSquared * NdotH * NdotH);
        float roughness = r1 * exp(r2);
        
        // fresnel
        // Schlick approximation
        float fresnel = pow(1.0 - VdotH, 5.0);
        fresnel *= (1.0 - F0);
        fresnel += F0;
 
        specular = (fresnel * geoAtt * roughness) / (NdotV * NdotL * 3.14);
	}
	if(keyF8) return 0;
	return specular;
}





void main()
{

vec3 lighting= vec3(0);

vec3 position_ViewSpace ;
	position_ViewSpace.z = -texture(gPosition, UV).r ;
	position_ViewSpace.x = -(UV.x*2-1)*position_ViewSpace.z*(aspect) *tanHalfFov ;
	position_ViewSpace.y = -(UV.y*2-1)*position_ViewSpace.z *tanHalfFov ;

vec3 normal = vec3(texture(gNormal, UV).rgb);
float emit = normal.z;
    normal.z= sqrt(1.0 - normal.x*normal.x - normal.y*normal.y); 

vec3 diffuse = texture(gDiffuse, UV).xyz;
float ao = texture(aoSampler,UV).x;
float bloom =  texture(bloomSampler,UV).x;


for(int k=0;k<2;k++){
	vec3 i = position_ViewSpace- (view* vec4(lights[k].position_WorldSpace,1)).xyz;
	float dist = length(i) *length(i);
	i=normalize(i);
	float alpha = dot(-i,normal);
	alpha = clamp(alpha,0,1);
	float attenuation = 1/( 1 + pow( dist/300.0,2)  );
	
	lighting += 0.1*diffuse+    1*(attenuation) * (alpha)*diffuse*lights[k].intensity*(1+0.4*Cook_Torrance(-i,vec3(0,0,1),normal,0.3,0.5));
}
if(!keyF4) lighting=lighting*(ao*1.0);


if(keyF1) lighting = normal;
if(keyF2) lighting = position_ViewSpace*vec3(1,1,-1);
if(keyF3) lighting = vec3(ao);

if(keyF7) lighting = vec3(emit);
else lighting = lighting+(diffuse+vec3(0.2))*(bloom*3) ;

if(keyF8) lighting = vec3(bloom);





outColor =		vec4(lighting*1.0,1);


}
