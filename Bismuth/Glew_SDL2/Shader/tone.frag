#version 330

in vec2 UV;
out vec4 outColor;

uniform sampler2D imageSampler;
uniform sampler2D bloomSampler1;
uniform sampler2D bloomSampler2;
uniform sampler2D bloomSampler3;
uniform sampler2D bloomSampler4;
uniform sampler2D lensFlareSampler;
uniform sampler2D lensStarSampler;
uniform sampler2D lensDirtSampler;
uniform mat2 matAngle;

vec3 darken(vec3 s){

float l = length(s);
vec3 d = normalize(s);
d = pow(d,vec3(3));
d = d*l;
d = max(vec3(0), d);
return d;

}


vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}


void main()
{



vec3 image = texture(imageSampler, UV).rgb;
vec3 bloom1 = texture(bloomSampler1, UV).rgb;
vec3 bloom2 = texture(bloomSampler2, UV+vec2(0,0.0125)).rgb;
vec3 bloom3 = texture(bloomSampler3, UV+vec2(0,0.025)).rgb;
vec3 bloom4 = texture(bloomSampler4, UV+vec2(0,0.05)).rgb;
vec2 UVRotated = matAngle*(UV-vec2(0.5)) +vec2(0.5);
vec3 lensFlare =  texture(lensFlareSampler,UV).rgb * (0.01+ texture(lensStarSampler,UVRotated).r* pow(texture(lensDirtSampler,UV).r,3) ) *1;

float k= 1;
float k1 =1;
float k2 =1;
float k3 =1;
float k4 =1;
float kl =0.5;

bloom1 = darken(bloom1);
bloom2 = darken(bloom2);
bloom3 = darken(bloom3);
bloom4 = darken(bloom4);



//
//k1 = 0;
//k2 = 0;
//k3 = 0;
//k4 = 0;

//if(gl_FragCoord.x < 750) 
//k4 = 1;


//if(gl_FragCoord.x < 770 && gl_FragCoord.x > 750 ) 
//k3 = 1;


//if(gl_FragCoord.x < 790 && gl_FragCoord.x > 770 ) 
//k2 = 1;

//if(gl_FragCoord.x > 790) 
//k1 = 1;

//if(gl_FragCoord.x > 820) {
//k1 = 1;
//k2 = 1;
//k3 = 1;
//k4 = 1;
//}



image+= k *( k1* bloom1 +k2*bloom2 + k3*bloom3 + k4*bloom4 ) +lensFlare*kl ;

image =  vec3(1.0) - exp(-image * 2);

outColor =		vec4(image,1);

}
