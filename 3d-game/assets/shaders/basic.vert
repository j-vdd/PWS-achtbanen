#version 420

in vec3 vPosition;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(vPosition, 1.0);
}