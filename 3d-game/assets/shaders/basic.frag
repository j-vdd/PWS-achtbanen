#version 420

out vec4 outColor;


layout (std140) uniform Material
{
    vec3 color;
	float specular;
};


void main()
{
	outColor = vec4(color, 1);
}