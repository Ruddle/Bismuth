#version 330

in vec2 UV;
out float outColor;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D image;
uniform int h;
uniform vec2 resolution;
uniform float size;

//uniform float offset[3] = float[]( 0.0, 1.3846153846, 3.2307692308 );
//uniform float weight[3] = float[]( 0.2270270270, 0.3162162162, 0.0702702703 );

 float offset[3] = float[]( 0.0, 1.3846153846+size, 3.2307692308+size*2 );
 float weight[3] = float[]( 0.2270270270, 0.3162162162, 0.0702702703 );


void main()
{

vec3 normal = vec3(texture(gNormal, UV).rg,0);
normal.z= sqrt(1.0 - normal.x*normal.x - normal.y*normal.y); 
normal = normalize(normal);

float depth = texture(gPosition, UV).r ;

float weightNormal;
float depthDiff ;
float weightDepth ;
vec3 normalOffset;
float totalWeight=0.2270270270;
float epsilon = 7*10e-4 * depth*10;

float blur = texture( image, UV ).r * weight[0];

    for (int i=1; i<3; i++) {
		
		depthDiff = depth - texture(gPosition,UV+ ( vec2(offset[i]*(1-h), h*offset[i]) )/resolution).r ;
		weightDepth = 1 / (epsilon + abs(depthDiff*depthDiff)); 
		normalOffset = vec3(texture(gNormal, UV+ ( vec2(offset[i]*(1-h), h*offset[i]) )/resolution).rg,0);
		normalOffset.z= sqrt(1.0 - normalOffset.x*normalOffset.x - normalOffset.y*normalOffset.y); 
		weightNormal = dot(normal, normalize(normalOffset));
		weightNormal = pow(weightNormal,2);
        blur +=   texture( image,UV+ ( vec2(offset[i]*(1-h), h*offset[i]) )/resolution ).r * weight[i] * weightDepth* weightNormal;
		totalWeight += weight[i] * weightDepth * weightNormal;

		depthDiff = depth - texture(gPosition, UV-(vec2(offset[i]*(1-h), h*offset[i]) )/resolution).r ;
		weightDepth = 1 / (epsilon + abs(depthDiff*depthDiff)); 
		normalOffset = vec3(texture(gNormal, UV+ ( vec2(offset[i]*(1-h), h*offset[i]) )/resolution).rg,0);
		normalOffset.z= sqrt(1.0 - normalOffset.x*normalOffset.x - normalOffset.y*normalOffset.y); 
		weightNormal = dot(normal, normalize(normalOffset));
		weightNormal = pow(weightNormal,2);
        blur +=   texture( image,UV-( vec2(offset[i]*(1-h), h*offset[i]) )/resolution ).r * weight[i] * weightDepth * weightNormal;
		totalWeight += weight[i] * weightDepth * weightNormal;
    }

outColor =		blur/totalWeight;
}
