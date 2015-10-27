#version 330

in vec3 inPosition;
in vec3 inNormal;
in vec2 inUV;

uniform mat4 projection;
uniform mat4 modelview;
uniform mat3 normal;

out vec2 varUV;
out vec3 varNormal;

void main()
{
    gl_Position = projection * modelview * vec4(inPosition, 1.0);
	varUV = inUV;
	varNormal = normal * inNormal;
}