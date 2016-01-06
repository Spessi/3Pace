#pragma once

#include <vector>
#include "SDLHelper.h"

class Heightmap {
public:
	Heightmap();
	~Heightmap();
	bool Heightmap::loadFromFile(std::string path);
	void draw();

private:
	GLuint m_VAO;
	GLuint m_VerticesVBO;
	GLuint m_IndicesVBO;
	GLuint m_VerticesCount;

};

