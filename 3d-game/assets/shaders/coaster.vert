#version 420

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoords;
layout(location = 3) in float vIndex;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

out vec3 fPosition;
out vec3 fNormal;
out float fIndex;

void main()
{
	fNormal = mat3(uModel) * vNormal;
	fIndex = vIndex;

	vec4 worldPosition = uModel * vec4(vPosition, 1.0);
	fPosition = worldPosition.xyz;
	gl_Position = uProjection * uView * worldPosition;
}