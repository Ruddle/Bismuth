#version 330

in vec3 varPosition;

out float depth;

void main()
{
	depth = -varPosition.z;
}
