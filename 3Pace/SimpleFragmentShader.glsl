#version 330 core

out vec4 color;
in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;
in vec3 ObjectColor;

void main() {
	vec3 lightColor = vec3(1.0, 1.0, 1.0);
	
	// Ambient
	float ambientStrength = 0.2f;
	vec3 ambient = ambientStrength * lightColor;
	
	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * ObjectColor;
	color = vec4(result, 1.0f);
}