#version 330

in vec3 inPosition;

uniform mat4 projection;
uniform mat4 modelview;

out vec3 varPosition;

void main()
{
	varPosition = (modelview* vec4(inPosition, 1.0)).xyz;
	gl_Position=  projection * modelview * vec4(inPosition, 1.0);;
}