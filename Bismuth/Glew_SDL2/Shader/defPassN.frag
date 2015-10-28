#version 330

in vec2 UV;
out vec4 outColor;

uniform sampler2D gNormal;
uniform sampler2D gDiffuse;
uniform sampler2D gPosition;

void main()
{

    outColor = texture(gDiffuse, vec2(0,-1)+UV*2) + 	   texture(gNormal, vec2(-1,-1)+UV*2)+ 	   texture(gPosition, vec2(-1,0)+UV*2)*vec4(1.0/1000.0,1.0/1000.0,1,1.0) ;
}
