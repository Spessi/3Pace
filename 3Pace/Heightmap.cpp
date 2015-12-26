#include "Heightmap.h"



Heightmap::Heightmap(std::string path) {
	SDL_Surface* img = IMG_Load("heightmap.png");
//	std::cout << "Bytes per Pixel: " << std::to_string(img->format->BytesPerPixel) << std::endl;
	GLuint index = 0;
	SDL_Color* color = nullptr;
	Uint8* pixels;
	pixels = (Uint8*)img->pixels;

	GLfloat pixelRatio = 65.536f / 256.0f; // 1px == 25,6cm
	GLfloat heightRatio = 1.0f;


	GLfloat* mHeightmapVertexData = (GLfloat*)malloc(sizeof(GLfloat) * img->w * img->h * 3);

	for (int y = 0; y < img->h; y++) {
		for (int x = 0; x < img->w; x++) {
			index = y*img->w + x;
			color = &img->format->palette->colors[pixels[index]];
			mHeightmapVertexData[index * 3 + 0] = x * pixelRatio;
			mHeightmapVertexData[index * 3 + 1] = y * pixelRatio;
			mHeightmapVertexData[index * 3 + 2] = color->r - 127;
//			std::cout << "Pixel [" << x << " / " << y << "]: " << "Index: " << (index) << " | " << std::to_string(pixels[index]) << " | " << std::to_string(color->r) << std::endl;
		}
	}
	
}


Heightmap::~Heightmap() {
	free(mHeightmapVertexData);
}
