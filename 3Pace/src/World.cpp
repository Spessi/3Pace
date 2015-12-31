#include "World.h"
GLuint gVAO = 0;
GLuint gVBO = 0;


void World::loadCube() {

	// make and bind the VAO
	glGenVertexArrays(1, &gVAO);
	glBindVertexArray(gVAO);

	// make and bind the VBO
	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);

	// Put the three triangle verticies into the VBO
	GLfloat vertexData[] = {
		//  X     Y     Z
		// Front
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,

		// Back
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		// Left
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,

		// Right
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData) * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

	// connect the xyz to the "vert" attribute of the vertex shader
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	// unbind the VBO and VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

World::World() {
	// Load all shaders
	std::vector<Shader> shaders;
	shaders.push_back(Shader("SimpleVertexShader.glsl", GL_VERTEX_SHADER));
	shaders.push_back(Shader("SimpleFragmentShader.glsl", GL_FRAGMENT_SHADER));
	m_ShaderProg = new ShaderProgram(shaders);

	// Set up the camera
	m_Camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f), 180.0f, 0.0f, true, 3.1f, 5.0f);

	loadCube();
}

World::~World() {
	delete m_ShaderProg;
	delete m_Camera;
}

void World::process(GLfloat delta) {
	int x, y;
	m_Delta = delta;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SDL_GetRelativeMouseState(&x, &y);
	m_Camera->processMouse(x, y, m_Delta);

	// Render
	render();
	// Render End
}


void World::render() {
	glm::mat4 mModelMatrix;

	// bind the program (the shaders)
	glUseProgram(m_ShaderProg->getProgramID());

	// Get the ModelViewProjection-PropertyID from the shader program
	GLuint mvpID = glGetUniformLocation(m_ShaderProg->getProgramID(), "MVP");

	// bind the VAO (the triangle)
	glBindVertexArray(gVAO);


	// draw the VAO
	mModelMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 5.0f, 0.0f));							// Position
	mModelMatrix = glm::rotate(mModelMatrix, glm::radians(m_Angle2), glm::vec3(1.0f, 0.0f, 0.0f));		// Rotation around origin
	mModelMatrix = glm::translate(mModelMatrix, glm::vec3(0.0f, 1.0f, 0.0f));							// Origin
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, glm::value_ptr(m_ProjectionMatrix * m_Camera->getViewMatrix() * mModelMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 24);
	mModelMatrix =  glm::rotate(glm::mat4(), glm::radians(m_Angle), glm::vec3(1.0f, 0.0f, 0.0f));
	m_Angle += 2.0f;
	m_Angle2 += 4.0f;
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, glm::value_ptr(m_ProjectionMatrix * m_Camera->getViewMatrix() * mModelMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 24);
	// unbind the VAO
	glBindVertexArray(0);

	glUseProgram(0);
}

void World::processKeyboard(SDL_Keycode key) {
	m_Camera->processKeyboard(key, m_Delta);
}

void World::setProjectionMatrix(glm::mat4 mat) {
	m_ProjectionMatrix = mat;
}

const ShaderProgram* World::getShaderProg() const {
	return m_ShaderProg;
}