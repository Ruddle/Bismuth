#version 330

in vec2 UV;
out vec4 outColor;


uniform sampler2D gPosition;
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

float doAO(int numPass,vec3 position,float radius) {

	float ao=0;
	for(float i =1;i<numPass+1;i++){

		float index = i+(pow(time,1.334))*0.348484657;
	
		float rand1 =	random(gl_FragCoord.xy*0.3153548679861*pow(index,2));
		float rand2 =	random(gl_FragCoord.xy*0.1461276795721*pow(index,3));
		float rand3 =	random(gl_FragCoord.xy*1.5364988515456*pow(index,4));
		float rand4 =	random(gl_FragCoord.xy*0.9876543598998*index);

				vec3 random3 = vec3(rand1,rand2,rand3) ;
				random3 = random3-vec3(0.5);
				random3 = normalize(random3);

				float length = rand4;
				length = pow(length,3);

				vec3 ray = length*radius*random3 + position.xyz;
				vec4 depthRay = projection*vec4(ray,1.0);
				depthRay.xy /= depthRay.w;
				depthRay.xy = depthRay.xy * 0.5 + vec2(0.5);

				if(gl_FragCoord.x>8000) {
					ao+= (-position.z >=  texture(gPosition, depthRay.xy ).r) ? 1.0:0.0;
				}

				else{
					float cut = 0.7;
					float ecart = -position.z -  texture(gPosition, depthRay.xy ).r;
					if(ecart>0){
						if(ecart<cut)
						ao++;
						else
						ao+=max(1+cut-ecart,0.5);
					}
				}
	}
	ao = ao/(numPass);
	return ao;
}


int NUMPASS=32;
float RADIUS = 1;

void main()
{

vec3 position_ViewSpace ;
	position_ViewSpace.z = -texture(gPosition, UV).r ;
	position_ViewSpace.x = -(UV.x*2-1)*position_ViewSpace.z*(aspect) *tanHalfFov ;
	position_ViewSpace.y = -(UV.y*2-1)*position_ViewSpace.z *tanHalfFov ;


float ao = doAO(NUMPASS,position_ViewSpace,RADIUS);
outColor =		vec4(vec3(1- ao)  ,1);
}
