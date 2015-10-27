#version 330

in vec3 Color;
in vec2 UV;
out vec4 outColor;

uniform sampler2D texture_diffuse;

void main()
{
    outColor = mix(vec4(Color,1),texture(texture_diffuse, UV),0.5);
}
