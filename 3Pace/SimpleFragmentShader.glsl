#version 330 core

smooth in vec3 theColor;
out vec4 LFragment;

void main() {
	LFragment = vec4( theColor, 1.0 );
}