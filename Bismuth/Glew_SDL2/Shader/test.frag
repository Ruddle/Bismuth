#version 150 core

in vec2 inUV;
out vec4 outColor;

uniform sampler2D texture;

void main()
{
    outColor = texture(texture, inUV);
}
