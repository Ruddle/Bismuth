#version 330

in vec2 UV;
out vec3 outColor;


uniform sampler2D image;
uniform int h;
uniform vec2 resolution;
uniform float size;

   vec3 textureDistorted(
      in sampler2D tex,
      in vec2 texcoord,
      in vec2 direction, // direction of distortion
      in vec3 distortion // per-channel distortion factor
   ) {
      return vec3(
         texture(tex, texcoord + direction * distortion.r).r,
         texture(tex, texcoord + direction * distortion.g).g,
         texture(tex, texcoord + direction * distortion.b).b
      );
   }

int numGhost = 6;
float dispersion = 0.2;

void main()
{
vec2 UVInv = vec2(1) - UV;
vec2 toCenter = vec2(0.5) - UV;
float dist = length(toCenter);
vec2 offset = ( vec2(0.5) - UVInv) * dispersion;

vec3 result = vec3(0);

for(int i=0; i< numGhost;i++) 
{
	vec2 offset2 = fract(UVInv + offset * float(i));
	//offset2+= haloVec;
	float weight = length(offset2-vec2(0.5)) / length(vec2(0.5));
	weight = pow(1-weight,10);
	weight = clamp(weight,0,1);
	result+= textureDistorted(image,offset2, offset2 , vec3(-1,0,1)/100.0)*weight;

	vec2 haloVec = normalize(offset) * 0.5;
	offset2 = fract(UVInv + offset * float(i));
	offset2+= haloVec;
	weight = length(offset2-vec2(0.5)) / length(vec2(0.5));
	weight = pow(1-weight,10);
	weight = clamp(weight,0,1);
	result+= textureDistorted(image,offset2, offset2 , vec3(-1,0,1)/150.0)*weight;
}

outColor =	result;
}
