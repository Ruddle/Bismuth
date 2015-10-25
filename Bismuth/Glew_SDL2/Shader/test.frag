#version 330

in vec2 UV;
out vec4 outColor;

uniform sampler2D texture_diffuse;

void main()
{
    outColor = texture(texture_diffuse, UV);
}
