#include "Heightmap.h"

Heightmap::Heightmap(std::string path) {
	GLuint pixelIndex = 0;
	const GLfloat pixelRatio = 65.536f / 256.0f; // 1px == 25,6cm
	const GLfloat heightRatio = 1.0f / 100.0f;	// 1 Unit = 1cm
	const GLfloat heightOffset = 127.0f;

	// Load heightmap (8-bit PNG, later it'll be 16 or 32-bit)
	SDL_Surface* img = IMG_Load("heightmap.png");

	// Reserve memory for the vertex data (w*h * 3 vertices)
	GLfloat* mHeightmapVertexData = (GLfloat*)malloc(sizeof(GLfloat) * img->w * img->h * 3);

	// Get Pixel data
	Uint8* pixels = (Uint8*)img->pixels;

	for (int y = 0; y < img->h; y++) {
		for (int x = 0; x < img->w; x++) {
			pixelIndex = y*img->w + x;
			// Get the color of the current pixel out of the colors palette
			SDL_Color color = img->format->palette->colors[pixels[pixelIndex]];

			// Vertex X component
			mHeightmapVertexData[pixelIndex * 3 + 0] = x * pixelRatio;
			// Vertex Y compoent
			mHeightmapVertexData[pixelIndex * 3 + 1] = y * pixelRatio;
			// Vertex Z component
			mHeightmapVertexData[pixelIndex * 3 + 2] = ((GLfloat)color.r - heightOffset) * heightRatio;
		}
	}

	// Relase memory from loaded heightmap
	SDL_FreeSurface(img);
}

Heightmap::~Heightmap() {
	free(mHeightmapVertexData);
}
