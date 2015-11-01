#version 330

in vec3 inPosition;
in vec3 inNormal;
in vec2 inUV;
in vec4 inColor;

uniform mat4 projection;
uniform mat4 modelview;

out vec2 UV;
out vec4 Color;

void main()
{
    gl_Position = projection * modelview * vec4(inPosition, 1.0);
	UV = inUV;
	Color=inColor;
}