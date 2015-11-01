#version 330

in vec4 Color;
in vec2 UV;
out vec4 outColor;

uniform sampler2D texture_diffuse;

void main()
{
    outColor = mix(vec4(Color.xyz,1.0),texture(texture_diffuse, UV),1-Color.a);
}
