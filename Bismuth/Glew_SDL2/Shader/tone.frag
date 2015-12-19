#version 330

in vec2 UV;
out vec4 outColor;

uniform sampler2D imageSampler;
uniform sampler2D bloomSampler1;
uniform sampler2D bloomSampler2;
uniform sampler2D bloomSampler3;
uniform sampler2D bloomSampler4;



void main()
{



vec3 image = texture(imageSampler, UV).rgb;
vec3 bloom1 = texture(bloomSampler1, UV).rgb;
vec3 bloom2 = texture(bloomSampler2, UV+vec2(0,0.0125)).rgb;
vec3 bloom3 = texture(bloomSampler3, UV+vec2(0,0.025)).rgb;
vec3 bloom4 = texture(bloomSampler4, UV+vec2(0,0.05)).rgb;

float k= 2;
float k1 = 0.4;
float k2 = 0.4;
float k3 = 0.4;
float k4 = 0.4;

//if(gl_FragCoord.x>900)
//{
////k1=0;
//k2=0;
//k3=0;
//}

//if(gl_FragCoord.x>800 && gl_FragCoord.x<900)
//{
//k1=0;
////k2=0;
//k3=0;
//}


//if(gl_FragCoord.x<800)
//{
//k1=0;
//k2=0;
////k3=0;
//}




image+= k *( k1* bloom1 +k2*bloom2 + k3*bloom3 + k4*bloom4 ) ;

image =  vec3(1.0) - exp(-image * 2);

outColor =		vec4(image,1);
}
