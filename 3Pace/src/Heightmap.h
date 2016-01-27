#pragma once

#include <vector>
#include "SDLHelper.h"

class Heightmap {
public:
	Heightmap();
	~Heightmap();
	bool Heightmap::loadFromFile(std::string path);
	GLuint getVAO();
	GLuint getVerticesCount();

private:
	int m_PixWidth;
	int m_PixHeight;
	GLuint m_VAO;
	GLuint m_VerticesVBO;
	GLuint m_IndicesVBO;
	GLuint m_VerticesCount;

	int getTriangleIndex(int x, int y);

};

