#version 330

in vec3 inPosition;
in vec3 inNormal;
in vec3 inTangent;
in vec3 inBitangent;
in vec2 inUV;

uniform mat4 projection;
uniform mat4 lastViewProjection;
uniform mat4 modelview;
uniform mat4 lastModel;
uniform mat3 normal;

out vec2 UV;
out vec3 varNormal;
out vec3 varTangent;
out vec3 varBitangent;
out vec3 varPosition;
out vec4 varCurrPosition_Proj;
out vec4 varPrevPosition_Proj;

void main()
{
   
	varPosition = (modelview* vec4(inPosition, 1.0)).xyz;
	UV = inUV;
	varNormal = normal * inNormal;
	varTangent = normal * inTangent;
	varBitangent = normal * inBitangent;





	varCurrPosition_Proj =  projection * modelview * vec4(inPosition, 1.0);
	varPrevPosition_Proj = lastViewProjection*lastModel *  vec4(inPosition, 1.0);

	gl_Position= varCurrPosition_Proj;
}