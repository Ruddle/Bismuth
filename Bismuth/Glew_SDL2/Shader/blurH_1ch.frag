#version 330

in vec2 UV;
out float outColor;

uniform sampler2D gNormal;
uniform sampler2D image;
uniform sampler2D gPosition;


uniform float offset[3] = float[]( 0.0, 1.3846153846, 3.2307692308 );
uniform float weight[3] = float[]( 0.2270270270, 0.3162162162, 0.0702702703 );



void main()
{




float blur = texture( image, vec2(gl_FragCoord)/vec2(1600,900) ) * weight[0];
    for (int i=1; i<3; i++) {
        blur +=
            texture( image, ( vec2(gl_FragCoord)+vec2(0.0, offset[i]) )/vec2(1600,900) )
                * weight[i];
        blur +=
            texture( image, ( vec2(gl_FragCoord)-vec2(0.0, offset[i]) )/vec2(1600,900) )
                * weight[i];
    }



outColor =		blur;
}
