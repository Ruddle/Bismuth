#version 150 core


in vec3 inPosition;
in vec3 inNormal;

uniform mat4 projection;
uniform mat4 modelview;

void main()
{
    gl_Position = projection * modelview * vec4(inPosition, 1.0);
}