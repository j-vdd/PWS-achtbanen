#version 420

layout (std140) uniform Material
{
    vec4 color;
	float smallGridEnabled;
	float specular;
};

layout (std140) uniform Scene
{
	vec3 uSunDirection;
};

uniform vec3 uCameraPosition;


in vec3 fPosition;
in vec3 fNormal;
in vec3 fLocal;

out vec4 outColor;

void main()
{
	vec3 fracPos = fract(fPosition);
	vec3 fracPos2 = fract(fPosition / 10);

	float dist = length(fLocal);
	float alpha = 1;

	float distFromLine = min(abs(fracPos.x - round(fracPos.x)), abs(fracPos.z - round(fracPos.z)));
	float distFromLine2 = min(abs(fracPos2.x - round(fracPos2.x)), abs(fracPos2.z - round(fracPos2.z)));
	if (smallGridEnabled < 0.5)
	{
		distFromLine = 1.0;
		distFromLine2 /= 2.0;
		dist /= 1.8;
	}

	if (distFromLine > 0.02 && distFromLine2 > 0.007)
	{
		alpha = max(max(0, 1 - (distFromLine - 0.02) * 30), 1 - (distFromLine2 - 0.007) * 300);//min(alpha, /*0.12 - distFromLine*/0.1);
	}

	alpha *= max(0.0, (0.7 - dist / 120));

	vec3 viewDir = normalize(uCameraPosition - fPosition);
	vec3 halfwayDir = normalize(-uSunDirection + viewDir);

	float spec = pow(max(dot(fNormal, halfwayDir), 0.0), specular) * 0.5;
	float shade = (dot(fNormal, -uSunDirection) + 1) / 2;

	outColor = vec4(color.rgb * clamp(shade, 0, 1) + color.rgb * clamp(spec, 0, 1), alpha);
}