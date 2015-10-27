#version 330

in vec3 inPosition;
in vec3 inNormal;
in vec2 inUV;

uniform mat4 projection;
uniform mat4 modelview;

out vec2 UV;

void main()
{
    gl_Position = projection * modelview * vec4(inPosition, 1.0);
	UV = inUV;
}