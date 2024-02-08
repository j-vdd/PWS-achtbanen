#version 420

layout (std140) uniform Material
{
    vec3 color;
};

uniform vec3 uCameraPosition;

out vec4 outColor;

void main()
{
	outColor = vec4(color, 1.0);
}