#version 330

in vec2 inPosition;
out vec2 UV;

uniform mat4 view;

void main()
{
    gl_Position = view*vec4(inPosition,0.0, 1.0);
	UV = (inPosition+vec2(1))/2.0;
}

