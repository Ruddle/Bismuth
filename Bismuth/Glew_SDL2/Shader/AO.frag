#version 330

in vec2 UV;
out float outColor;


uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D noiseSampler;
uniform vec3 samples[64];
uniform mat4 projection;
uniform float time;
uniform vec2 resolution;
uniform float aspect;
uniform float tanHalfFov;
uniform float near;
uniform float far;






uint hash( uint x ) {
    x += ( x << 10u );
    x ^= ( x >>  6u );
    x += ( x <<  3u );
    x ^= ( x >> 11u );
    x += ( x << 15u );
    return x;
}

uint hash( uvec2 v ) {
    return hash( v.x ^ hash(v.y) );
}

float random( float f ) {
    const uint mantissaMask = 0x007FFFFFu;
    const uint one          = 0x3F800000u;
    
    uint h = hash( floatBitsToUint( f ) );
    h &= mantissaMask;
    h |= one;
    
    float  r2 = uintBitsToFloat( h );
    return r2 - 1.0;
}

float random( vec2 f ) {
    const uint mantissaMask = 0x007FFFFFu;
    const uint one          = 0x3F800000u;
    
    uint h = hash( floatBitsToUint( f ) );
    h &= mantissaMask;
    h |= one;
    
    float  r2 = uintBitsToFloat( h );
    return r2 - 1.0;
}

float doAO(int numPass,vec3 position,vec3 normal,float radius) {

	float ao=0;
	vec4 randwi = texture(noiseSampler,UV*4.0).rgba;

	for(int i =0;i<numPass;i++){

		vec4 rand = vec4(0);

		rand.xyz = reflect(samples[i],randwi.xyz);
		rand.a = randwi.a;

		vec3 random3 = rand.xyz ;
	
		random3 = normalize(random3);
			
			//	if(dot(normal,random3)<0)
			//	random3 = -random3;
			//  Equivaut � : 
		random3 = -faceforward(random3,normal,random3);

		float length = rand.a;
		length = pow(length,2);

		vec3 ray = length*radius*random3 + position.xyz;
		vec4 depthRay = projection*vec4(ray,1.0);
		depthRay.xy /= depthRay.w;
		depthRay.xy = depthRay.xy * 0.5 + vec2(0.5);

		float cut = radius*1;
		float ecart = -position.z -  texture(gPosition, depthRay.xy ).r;

			//if(ecart>0){
			//if(ecart<cut)
			//ao+= 1-normal.z*0.8; 
			//else
			//ao+=max(2*cut-ecart,0);
			//}	
			// Equivaut � :
		ao+= (ecart>0)? ((ecart<cut)? (1-normal.z*0.8) : max(2*cut-ecart,0)*(1-normal.z*0.8) ):0.0 ;	
	}
	ao = ao/(numPass);
	return ao;
}


int NUMPASS=10;
float RADIUS = 1;

void main()
{

vec3 position_ViewSpace ;
	position_ViewSpace.z = -texture(gPosition, UV).r ;
	position_ViewSpace.x = -(UV.x*2-1)*position_ViewSpace.z*(aspect) *tanHalfFov ;
	position_ViewSpace.y = -(UV.y*2-1)*position_ViewSpace.z *tanHalfFov ;

vec3 normal = vec3(texture(gNormal, UV).rg,0);
				normal.z= sqrt(1.0 - normal.x*normal.x - normal.y*normal.y); 


float ao = doAO(NUMPASS,position_ViewSpace,normal,RADIUS);


ao = 1-ao;

float lost = 0.3;
//ao = (max(ao,lost)-lost)/(1-lost);

outColor =		pow(ao,1);

//outColor = texture(noiseSampler,UV*vec2(4.0)).r/2.0+0.5;
}
