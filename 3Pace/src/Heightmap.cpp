#include "Heightmap.h"



Heightmap::Heightmap() {
	m_VerticesCount = 0;
}


Heightmap::~Heightmap() {
}

bool Heightmap::loadFromFile(std::string path) {
	// Load heightmap (8-bit PNG, later it'll be 16 or 32-bit)
	SDL_Surface* img = IMG_Load(path.c_str());

	if (img == nullptr)
		return false;

	// Get Pixel data
	Uint8* pixels = (Uint8*)img->pixels;
	
	// Load vertices into vector
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	for (int y = 0; y < img->h; y++) {
		for (int x = 0; x < img->w; x++) {
			GLuint pixIndex = y*img->w + x;
			SDL_Color color = img->format->palette->colors[pixels[pixIndex]];

			// Distance between the vertices
			GLfloat gridWidth = 1.0f / ((GLfloat)img->w - 1.0f);
			GLfloat gridHeight = 1.0f / ((GLfloat)img->h - 1.0f);

			// Map offset (locally centered)
			GLfloat offsetX = -img->w / 2.0f;
			GLfloat offsetY = -img->h / 2.0f;

			Vertex vertex;
			vertex.position.x = offsetX + (GLfloat)x;
			vertex.position.y = (GLfloat)color.r / 8.0f;
			vertex.position.z = offsetY + (GLfloat)y;
			vertex.normal.x = 0;
			vertex.normal.y = 0;
			vertex.normal.z = 0;
			vertices.push_back(vertex);

			if (x < (img->w - 1) && y < (img->h - 1)) {
				indices.push_back(x + y*img->w);
				indices.push_back(x + (y + 1)*img->w);
				indices.push_back((x + 1) + y*img->w);

				indices.push_back((x + 1) + y*img->w);
				indices.push_back(x + (y + 1)*img->w);
				indices.push_back((x + 1) + (y + 1)*img->w);

				m_VerticesCount += 6;
			}
		}
	}
	// Relase memory from loaded heightmap
	SDL_FreeSurface(img);

	// Create Vertex Buffer Object for the vertices and bind it
	glGenBuffers(1, &m_VerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);
	// Upload the vertices to the VBO
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	// Create Vertex Buffer Object for the indices and bind it
	glGenBuffers(1, &m_IndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesVBO);
	// Upload the indices to the VBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);




	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// Load vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Load indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesVBO);


	// Unload the previously created VBO and VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
}

void Heightmap::draw() {
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_VerticesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}