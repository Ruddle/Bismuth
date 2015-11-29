#version 330

in vec2 inPosition;
out vec2 UV;

uniform mat4 view;
uniform mat4 toUV;

void main()
{
    gl_Position = view*vec4(inPosition,0.0, 1.0);
	UV =vec2( toUV*    vec4(       (inPosition+vec2(1))/2.0,0,1));
}

