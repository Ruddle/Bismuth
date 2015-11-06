#version 330

in vec2 UV;
out vec4 outColor;

uniform sampler2D imageSampler;
uniform sampler2D bloomSampler;






void main()
{
vec3 image = texture(imageSampler, UV).rgb;
vec3 bloom = texture(bloomSampler, UV).rgb;

image+= bloom*1;

image =  vec3(1.0) - exp(-image * 2.5);

outColor =		vec4(image,1);
}
