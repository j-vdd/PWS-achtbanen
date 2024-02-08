#version 420

layout (std140) uniform Material
{
    vec3 color;
	float specular;
	float trackIndex;
};

layout (std140) uniform Scene
{
	vec3 uSunDirection;
};

uniform vec3 uCameraPosition;

in vec3 fPosition;
in vec3 fNormal;
in float fIndex;

out vec4 outColor;

void main()
{
	vec3 diffuse = color;
	if (abs(fIndex - trackIndex) < 0.01)
	{
		diffuse = vec3(1.0, 0.0, 0.0);
	}
	if (abs(fIndex + 1.0) < 0.01)
	{
		diffuse = vec3(0.9);
	}

	vec3 viewDir = normalize(uCameraPosition - fPosition);
	vec3 halfwayDir = normalize(-uSunDirection + viewDir);

	float spec = pow(max(dot(fNormal, halfwayDir), 0.0), specular) * 0.5;
	float shade = (dot(fNormal, -uSunDirection) + 1) / 2;
	outColor = vec4(diffuse * shade + diffuse * spec, 1.0);
}