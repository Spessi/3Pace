#include "Heightmap.h"



Heightmap::Heightmap() {
	m_VerticesCount = 0;
}


Heightmap::~Heightmap() {
}

int Heightmap::getTriangleIndex(int x, int y) {
	return 2 * x + 2 * y * (m_PixWidth - 1);
}

bool Heightmap::loadFromFile(std::string path) {
	// Load heightmap (8-bit PNG, later it'll be 16 or 32-bit)
	SDL_Surface* img = IMG_Load(path.c_str());

	if (img == nullptr)
		return false;

	m_PixWidth = img->w;
	m_PixHeight = img->h;

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

			// Create vertex
			Vertex vertex;
			vertex.position.x = offsetX + (GLfloat)x;
			vertex.position.y = (GLfloat)color.r / 8.0f;
			vertex.position.z = offsetY + (GLfloat)y;
			vertex.normal.x = 0;
			vertex.normal.y = 0;
			vertex.normal.z = 0;
			vertices.push_back(vertex);

			// Create indices
			if (x < (img->w - 1) && y < (img->h - 1)) {
				// Top Left triangle in quad
				indices.push_back(x + y*img->w);
				indices.push_back(x + (y + 1)*img->w);
				indices.push_back((x + 1) + y*img->w);

				// Bottom Right triangle in quad
				indices.push_back((x + 1) + y*img->w);
				indices.push_back(x + (y + 1)*img->w);
				indices.push_back((x + 1) + (y + 1)*img->w);

				m_VerticesCount += 6;
			}
		}
	}


	// Calculate face normals
	std::vector<glm::vec3> face_normals;
	for (int y = 0; y < img->h-1; y++) {
		for (int x = 0; x < img->w-1; x++) {
			// Get Top Left triangle
			Vertex vertex00 = vertices.at(x + y*img->w);
			Vertex vertex01 = vertices.at(x + (y + 1)*img->w);
			Vertex vertex02 = vertices.at((x + 1) + y*img->w);

			// Calculate Top Left normal
			glm::vec3 vector01 = vertex00.position - vertex01.position;
			glm::vec3 vector02 = vertex01.position - vertex02.position;
			glm::vec3 triangleNorm0 = glm::normalize(glm::cross(vector01, vector02));
			face_normals.push_back(triangleNorm0);


			// Get Bottom Right triangle
			Vertex vertex10 = vertices.at((x + 1) + y*img->w);
			Vertex vertex11 = vertices.at(x + (y + 1)*img->w);
			Vertex vertex12 = vertices.at((x + 1) + (y + 1)*img->w);

			// Calculate Bottom Right normal
			glm::vec3 vector11 = vertex10.position - vertex11.position;
			glm::vec3 vector12 = vertex11.position - vertex12.position;
			glm::vec3 triangleNorm1 = glm::normalize(glm::cross(vector11, vector12));
			face_normals.push_back(triangleNorm1);
		}
	}

	// Calculate average normal vector for each vertex
	glm::vec3 vert;
	for (int y = 0; y < img->h; y++) {
		for (int x = 0; x < img->w; x++) {
			int index = x + y * img->w;

			if (y == 0) {
				// First row

				if (x == 0)
					vert = face_normals.at(getTriangleIndex(x, y));	// Top Left triangle
				else if (x == img->w - 1)
					vert = face_normals.at(getTriangleIndex(x-1, y)) + face_normals.at(getTriangleIndex(x-1, y) + 1);	// Top Right triangle
				else
					vert = face_normals.at(getTriangleIndex(x-1, y)) + face_normals.at(getTriangleIndex(x-1, y) + 1) + face_normals.at(getTriangleIndex(x, y));	// Top Middle triangle
			}
			else if (y == img->h - 1) {
				// Bottom row

				if (x == 0)
					vert = face_normals.at(getTriangleIndex(x, y-1)) + face_normals.at(getTriangleIndex(x, y-1) + 1);	// Bottom Left triangle
				else if (x == img->w - 1)
					vert = face_normals.at(getTriangleIndex(x-1, y-1) + 1);	// Bottom right triangle
				else
					vert = face_normals.at(getTriangleIndex(x-1, y-1) + 1) + face_normals.at(getTriangleIndex(x, y-1)) + face_normals.at(getTriangleIndex(x, y-1) + 1);	// Bottom Middle triangle
			}
			else {
				// Middle row
				if (x == 0)
					vert = face_normals.at(getTriangleIndex(x, y-1)) + face_normals.at(getTriangleIndex(x, y-1) + 1) + face_normals.at(getTriangleIndex(x, y));	// Middle Left triangle
				else if (x == img->w - 1)
					vert = face_normals.at(getTriangleIndex(x-1, y-1) + 1) + face_normals.at(getTriangleIndex(x-1, y)) + face_normals.at(getTriangleIndex(x-1, y) + 1);	// Middle Right triangle
				else
					vert = face_normals.at(getTriangleIndex(x - 1, y - 1) + 1) + face_normals.at(getTriangleIndex(x - 1, y)) + face_normals.at(getTriangleIndex(x - 1, y) + 1) +
						     face_normals.at(getTriangleIndex(x, y - 1)) + face_normals.at(getTriangleIndex(x, y-1) + 1) + face_normals.at(getTriangleIndex(x, y));	// Middle Middle triangle
			}

			vert = glm::normalize(vert);
			vertices.at(index).normal = vert;
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



	// Create and fill the Vertex Array Object
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// Load vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Load normals
	glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

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