#version 420

in vec2 vPosition;

uniform vec2 uPosition;
uniform vec2 uDimensions;

void main()
{
	gl_Position = vec4(uDimensions * vPosition + uPosition, 0.0, 1.0);
}