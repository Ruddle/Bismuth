#version 330

in vec2 UV;
out vec3 outColor;


uniform sampler2D image;
uniform sampler2D speed;
uniform vec2 resolution;
uniform float size;
uniform float factor;

 float offset[3] = float[]( 0.0, 1.3846153846+size, 3.2307692308+size*2 );
 float weight[3] = float[]( 0.2270270270, 0.3162162162, 0.0702702703 );


void main()
{

vec3 blur = texture( image, UV ).rgb * weight[0];
vec2 speedOffset = factor*texture( speed, UV ).rg;

    for (int i=1; i<3; i++) {
        blur +=   texture( image,UV+(speedOffset*offset[i])/resolution ).rgb * weight[i];
        blur +=   texture( image,UV-(speedOffset*offset[i])/resolution ).rgb * weight[i];
    }

outColor = blur*1;
}
