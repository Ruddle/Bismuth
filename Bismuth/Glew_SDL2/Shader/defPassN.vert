#version 330

in vec2 inPosition;
out vec2 UV;

void main()
{
    gl_Position = vec4(inPosition,0.0, 1.0);
	UV = (inPosition+vec2(1))/2.0;
}