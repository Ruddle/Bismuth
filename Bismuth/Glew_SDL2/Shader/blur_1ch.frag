#version 330

in vec2 UV;
out float outColor;


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
float blur = texture( image, vec2(gl_FragCoord)/resolution ).r * weight[0];

    for (int i=1; i<3; i++) {
        blur +=   texture( image, ( vec2(gl_FragCoord)+vec2(offset[i]*(1-h), h*offset[i]) )/resolution ).r * weight[i];
        blur +=   texture( image, ( vec2(gl_FragCoord)-vec2(offset[i]*(1-h), h*offset[i]) )/resolution ).r * weight[i];
    }

outColor =		blur;
}
