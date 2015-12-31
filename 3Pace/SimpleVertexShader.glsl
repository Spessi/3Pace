#version 330 core

layout(location = 0) in vec3 LVertexPos3D;
layout(location = 1) in vec3 inColor; 

smooth out vec3 theColor;
uniform mat4 MVP;

void main() {
	gl_Position = MVP * vec4(LVertexPos3D, 1.0);
//	theColor = inColor;
	theColor = vec3(1.0, 1.0, 0.0);
//	gl_Position.xyz = LVertexPos3D;
//	gl_Position.w = 1.0;
}