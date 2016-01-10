#version 330 core

layout(location = 0) in vec3 position; 
layout(location = 1) in vec3 normal;

uniform mat4 projection, modelview;
uniform vec3 lightPos, objectColor;

out vec3 Normal;
out vec3 FragPos;
out vec3 LightPos;
out vec3 ObjectColor;

void main() {
	gl_Position = projection * modelview * vec4(position, 1.0);
	
	Normal = mat3(transpose(inverse(modelview))) * normal;
	FragPos = vec3(modelview * vec4(position, 1.0));
	LightPos = lightPos;
	ObjectColor = objectColor;
}