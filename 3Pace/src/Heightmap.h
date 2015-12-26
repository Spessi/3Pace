#pragma once
#include <string>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

class Heightmap
{
public:
	Heightmap(std::string path);
	~Heightmap();

private:
	GLfloat* mHeightmapVertexData;
};

