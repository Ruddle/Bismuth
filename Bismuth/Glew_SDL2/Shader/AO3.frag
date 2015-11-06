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
	for(float i =1;i<numPass+1;i++){

		float index = 1001*i+(pow(time,1.334))*0.348484657;
		float rand1 =	random(gl_FragCoord.xy*0.3153548679861*pow(index,2.3513));
		float rand2 =	random(gl_FragCoord.xy*0.1461276795721*pow(index,3.545));
		float rand3 =	random(gl_FragCoord.xy*0.9876543598998*index);

		vec2 offset = vec2(rand1,rand2)-vec2(0.5) ;
		offset = float(i)/10.0*normalize(offset)*radius/position.z;


		vec3 position2 ;
		position2.z = -texture(gPosition, UV + offset ).r ;
		position2.x = -(UV.x*2-1)*position2.z*(aspect) *tanHalfFov ;
		position2.y = -(UV.y*2-1)*position2.z *tanHalfFov ;
		
		vec3 diff = position2 - position;
		vec3 v = normalize(diff);
		float d = length(diff)*1;
		ao+=   max(0.0,dot(normal,v)-0.0)*2;//*(1.0/(1.0+d))*2.0


						
	}
	ao = ao/(numPass);
	return ao;
}


int NUMPASS=32;
float RADIUS =0.1;

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
}
