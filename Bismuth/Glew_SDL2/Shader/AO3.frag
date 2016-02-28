#version 330

in vec2 UV;
out float outColor;


uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform mat4 projection;
uniform float time;
uniform vec2 resolution;
uniform float aspect;
uniform float tanHalfFov;
uniform float near;
uniform float far;




#define SAMPLES 16   // More than 1, 80 max ( FullHD - 870M GTX)
#define DISTANCE 3. // Try between 0.5 - 5 
#define INTENSITY 3.

#define SCALE 0.005
#define BIAS 0.05
#define SAMPLE_RAD 1*DISTANCE
#define MAX_DISTANCE 30.


vec3 decodeNormal(vec2 enc){
	vec3 normal;
	 vec2 fenc = enc.xy*4.0;
    float f = dot(fenc,fenc);
    float g = sqrt(1-f/4);
    normal.xy = fenc*g;
    normal.z = 1-f/2;
	normal = normalize(normal);
	return normal;
}


vec3 getPosition(vec2 uv){


	vec3 position_ViewSpace ;
	position_ViewSpace.z = -texture(gPosition, uv).r ;
	position_ViewSpace.x = -(uv.x*2-1)*position_ViewSpace.z*(aspect) *tanHalfFov ;
	position_ViewSpace.y = -(uv.y*2-1)*position_ViewSpace.z *tanHalfFov ;
	
	return position_ViewSpace;
}



highp float rand(vec2 co)
{
    highp float a = 12.9898;
    highp float b = 78.233;
    highp float c = 43758.5453;
    highp float dt= dot(co.xy ,vec2(a,b));
    highp float sn= mod(dt,3.14);
    return fract(sin(sn) * c);
}




float doAmbientOcclusion(in vec2 tcoord,in vec2 uv, in vec3 p, in vec3 cnorm)
{
    vec3 diff = getPosition(tcoord + uv) - p;
    float l = length(diff);
    vec3 v = diff/l;
    float d = l*SCALE;
    float ao = max(0.0,dot(cnorm,v)-BIAS  )*(1.0/(1.0+d));
    
    float maxd = MAX_DISTANCE*length(uv)*(1.*float(SAMPLES));
    ao *= smoothstep(maxd,maxd * 0.5, l);
    return ao;

}


float spiralAO(vec2 uv, vec3 p, vec3 n, float rad)
{
    float goldenAngle = 2.39996;
    float ao = 0.0;
    float inv = 1. / float(SAMPLES);
    float radius = 0.;
    float rotatePhase = rand(uv*1.) * 6.28; 
    float rStep = inv * rad;
    vec2 spiralUV;

    for (int i = 0; i < SAMPLES; i++) {
        spiralUV.x = sin(rotatePhase);
        spiralUV.y = cos(rotatePhase);
        radius += rStep * float( (i+1)*(i+1)) /float(SAMPLES*SAMPLES) * 3. / 2.     ;

        float randomRadius = 0.6 + 0.8 * rand(vec2(sin(float(i)+uv.y),cos(float(i)+uv.x)));
    
      
       ao += doAmbientOcclusion(uv, spiralUV * radius * randomRadius, p, n)  ;
       rotatePhase += goldenAngle;
    }
    ao *= inv;
   
    return ao;
}




















void main()
{

vec3 position_ViewSpace =getPosition(UV);

vec3 normal = vec3(texture(gNormal, UV).rg,0);
	normal = decodeNormal(normal.xy);



  float rad = SAMPLE_RAD/position_ViewSpace.z;
  float  ao = spiralAO(UV, position_ViewSpace, normal, rad);



ao = 1-ao*INTENSITY;

outColor =		pow(ao,1);
}
