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

Heightmap heightmap;
World::World() {
	// Load all shaders
	std::vector<Shader> shaders;
	shaders.push_back(Shader("SimpleVertexShader.glsl", GL_VERTEX_SHADER));
	shaders.push_back(Shader("SimpleFragmentShader.glsl", GL_FRAGMENT_SHADER));
	m_ShaderProg = new ShaderProgram(shaders);

	// Set up the camera
	m_Camera = new Camera(glm::vec3(0.0f, 1.8f, 0.0f), 180.0f, 0.0f, 0.1f, 1000.0f, 16.0f/9.0f, true, 30.0f, 5.0f);

	heightmap.loadFromFile("heightmap.png");
}

World::~World() {
	delete m_ShaderProg;
	delete m_Camera;
}

void World::process(GLfloat delta) {
	m_Delta = delta;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_Camera->processKeyboard(m_Delta);
	m_Camera->processMouse(m_Delta);

	// Render
	render();
	// Render End
}


void World::render() {
	glm::mat4 modelMatrix;

	// bind the program (the shaders)
	glUseProgram(m_ShaderProg->getProgramID());

	// Get the ModelViewProjection-PropertyID from the shader program
	GLuint projectionLoc = glGetUniformLocation(m_ShaderProg->getProgramID(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(m_Camera->getProjectionMatrix()));
	GLuint modelviewLoc = glGetUniformLocation(m_ShaderProg->getProgramID(), "modelview");



	glBindVertexArray(gVAO);
	// draw the VAO
	glDrawArrays(GL_TRIANGLES, 0, 24);
	glBindVertexArray(0);

	modelMatrix = glm::mat4();
	glUniformMatrix4fv(modelviewLoc, 1, GL_FALSE, glm::value_ptr(m_Camera->getViewMatrix() * modelMatrix));
	heightmap.draw();

	glUseProgram(0);
}



const ShaderProgram* World::getShaderProg() const {
	return m_ShaderProg;
}

Camera* World::getCamera() {
	return m_Camera;
}