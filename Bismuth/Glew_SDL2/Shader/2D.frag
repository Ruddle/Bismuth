#version 330

in vec2 UV;
uniform sampler2D texture_diffuse;
layout (location = 0) out vec4 outColor;


void main()
{

outColor = vec4(texture(texture_diffuse,UV));
}


//vec2 center = (UV-vec2(0.5)) *2;

//float dist = length(center);
//float proxy = pow(1-dist,0.2);

// outColor = vec4(pow(proxy,8),pow(proxy,4),1,proxy);