#version 330

in vec2 UV;
out vec4 outColor;

uniform sampler2D gNormal;
uniform sampler2D gDiffuse;
uniform sampler2D gPosition;
uniform mat4 projection;

const float NEAR = 0.10f; // projection matrix's near plane
const float FAR = 100.0f; // projection matrix's far plane
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * NEAR * FAR) / (FAR + NEAR - z * (FAR - NEAR));	
}

#define M_PI 3.1415926535897932384626433832795
#define M_HALFPI 3.1415926535897932384626433832795/2.0



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


float radius = 0.01;

void main()
{
vec3 position = texture(gPosition, vec2(0,0)+UV).xyz;

float depth = LinearizeDepth(position.z);

float ao=0;

for(float i =0;i<5;i++){
	for(float j =0;j<5;j++){
		for(float k =0;k<5;k++){

			vec3 random3 = vec3(      random(gl_FragCoord.xy*i+j*k),random(gl_FragCoord.xy*j+i*k),random(gl_FragCoord.xy*k+i*j)) ;
			random3 = random3-vec3(0.5);
			random3 = normalize(random3);

			float length = random(gl_FragCoord.xy*i*j*k);
			length = pow(length,2);

			vec3 ray = length*radius*random3 + position;

			//ray=position;
			

			vec4 depthRay = projection*vec4(ray,1.0);
		//	depthRay.xy /= depthRay.w;
		//	depthRay.xy = depthRay.xy * 0.5 + 0.5;

			if(depth> LinearizeDepth(depthRay.z)) 
			ao++;

		}
	}
}
ao = ao/pow(5.0,3.0);


outColor =		vec4(vec3(ao),1);
}
