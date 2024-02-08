#version 420

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoords;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

out vec3 fPosition;
out vec3 fNormal;
out vec3 fLocal;

void main()
{
	fNormal = mat3(uModel) * vNormal;

	vec4 worldPosition = uModel * vec4(vPosition, 1.0);
	fPosition = worldPosition.xyz;

	vec4 localPosition = uView * worldPosition;
	fLocal = localPosition.xyz;
	gl_Position = uProjection * localPosition;
}