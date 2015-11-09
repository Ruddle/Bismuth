#version 330

in vec2 UV;
layout (location = 0) out vec3 outColor;
layout (location = 1) out vec3 outBloom;

uniform sampler2D gNormal;
uniform sampler2D gDiffuse;
uniform sampler2D gPosition;
uniform sampler2D aoSampler;
uniform sampler2D shadowSampler;
uniform mat4 view;
uniform mat4 invView;
uniform mat4 viewLight;
uniform mat4 projectionLight;
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
uniform bool keyF9;
uniform bool keyF10;
uniform int AO;


struct Light
{
  vec3 position_WorldSpace;
  vec3 intensity;
};

const Light lights[2] = Light[2](  Light(vec3(10,-4,1),vec3(1,0.9,0.8))  ,   Light(vec3(-10,-4,10),vec3(0.8,0.9,1))  );



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

if(AO!=1) 
ao=1;


float specFactor =texture(gDiffuse, UV).a;

//SHADOW
vec4 positionFromCam_WorldSpace = invView*vec4(position_ViewSpace,1);
vec4 positionFromCam_ViewLightSpace = viewLight *positionFromCam_WorldSpace;
vec4 positionFromCam_ScreenLightSpace = projectionLight*positionFromCam_ViewLightSpace;
positionFromCam_ScreenLightSpace /= positionFromCam_ScreenLightSpace.w; 
vec2 offset  = (positionFromCam_ScreenLightSpace).xy;
offset = (offset*0.5) +0.5;
float shadow =   -texture(shadowSampler,offset).x - positionFromCam_ViewLightSpace.z -0.1 ;
shadow = shadow>0 ? 1:0;


for(int k=0;k<2;k++){
	vec3 i = position_ViewSpace- (view* vec4(lights[k].position_WorldSpace,1)).xyz;
	float dist = length(i) *length(i);
	i=normalize(i);
	float alpha = dot(-i,normal);
	alpha = clamp(alpha,0,1);
	float attenuation = 1/( 1 + pow( dist/300.0,2)  );
	
	lighting += 0.03*diffuse+    (1-shadow*0.5)*(attenuation) * (alpha)*diffuse*lights[k].intensity*(1+1*specFactor*Cook_Torrance(-i,normalize(-position_ViewSpace),normal,0.25,0.8));
}

if(!keyF4) lighting=lighting*(ao*2-1);


if(keyF1) lighting = normal;
if(keyF2) lighting = position_ViewSpace*vec3(1,1,-1);
if(keyF3) lighting = vec3(ao);

if(keyF7) lighting = vec3(emit);

outColor = lighting + emit*5 * (diffuse + vec3(0.0));

float brightness = dot(outColor, vec3(0.2126, 0.7152, 0.0722));

outBloom = (brightness >1) ? outColor:vec3(0) ;

if(keyF8) {
outColor = outBloom;
}
if(keyF9) outColor = vec3(specFactor);


if(keyF1 || keyF2|| keyF3|| keyF6|| keyF7|| keyF8 ||keyF9 ||keyF10)
outBloom = vec3(0);







if(keyF10) outColor = vec3(pow(texture(shadowSampler,UV).x,1)/50.0);
if(keyF10) outColor = vec3(shadow);
}
