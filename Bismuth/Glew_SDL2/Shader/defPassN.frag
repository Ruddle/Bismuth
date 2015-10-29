#version 330

in vec2 UV;
out vec4 outColor;

uniform sampler2D gNormal;
uniform sampler2D gDiffuse;
uniform sampler2D gPosition;

void main()
{
vec3 lightPosition_ViewSpace = vec3(800+800,450+450,-100);
vec3 position = texture(gPosition, vec2(0,0)+UV*2).xyz;
vec3 normal   = texture(gNormal, vec2(0,0)+UV*2).xyz;
vec3 diffuse = texture(gDiffuse, vec2(0,0)+UV*2).xyz;

vec3 i = position-lightPosition_ViewSpace;
float dist = length(i) *length(i);
i=normalize(i);

float alpha = dot(-i,normal);
alpha = clamp(alpha,0,1);

float attenuation = (1/(dist/500000));

vec3 lighting =attenuation* (alpha+0.2)*diffuse;


if(gl_FragCoord.x>800 ||gl_FragCoord.y>450)
lighting=vec3(0);

    outColor =	texture(gDiffuse, vec2(0,-1)+UV*2) + 
				texture(gNormal, vec2(-1,-1)+UV*2) + 	 
			    texture(gPosition, vec2(-1,0)+UV*2)*vec4(1.0/1000.0,1.0/1000.0,1,1.0) +
				vec4(lighting,1);
}
