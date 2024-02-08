#version 420

layout(location = 0) in vec2 vPosition;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(vPosition.x, 0.01, -vPosition.y, 1.0);
}