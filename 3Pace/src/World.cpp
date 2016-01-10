#include "World.h"

World::World() {
}

World::~World() {
	delete m_ShaderProg;
	delete m_Camera;
}

bool World::init() {
	m_DrawWireframe = false;

	
	// Load all shaders
	std::vector<Shader> shaders;
	Shader shader;
	shader.load("SimpleVertexShader.glsl", GL_VERTEX_SHADER);
	shaders.push_back(shader);
	shader.load("SimpleFragmentShader.glsl", GL_FRAGMENT_SHADER);
	shaders.push_back(shader);


	m_ShaderProg = new ShaderProgram();
	m_ShaderProg->compileProgram(shaders);



	m_Camera = new Camera();
	// Set up the camera to position (0/20/0) with a movement speed of 30
	m_Camera->init(glm::vec3(0.0f, 50.0f, 0.0f), 180.0f, 0.0f, 0.1f, 1000.0f, 16.0f / 9.0f, true, 30.0f, 5.0f);

	m_Heightmap.loadFromFile("heightmap.png");
	


	// TODO: do some error testing
	return true;
}

void World::process(GLfloat delta) {
	m_Delta = delta;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const Uint8* state = SDL_GetKeyboardState(NULL);
	// Enable / Disable Wireframe mode with key 1 / key 2
	if (state[SDL_SCANCODE_1])
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (state[SDL_SCANCODE_2])
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Do camera movement
	m_Camera->processKeyboard(m_Delta);
	m_Camera->processMouse(m_Delta);


	// Render
	render();
	// Render End
}

void World::render() {
	glm::mat4 modelMatrix;
	static float angle = 0.0f;

	// bind the program (the shaders)
	glUseProgram(m_ShaderProg->getProgramID());

	// Transform light position (0/100/0) into ModelView space
	glm::vec3 lightPos = glm::vec3(m_Camera->getViewMatrix() * modelMatrix * glm::vec4(0.0f, 100.0f, 0.0f, 1.0f));
	glUniform3fv(m_ShaderProg->getUniformLoc("lightPos"), 1, glm::value_ptr(lightPos));

	// Get the ModelViewProjection-PropertyID from the shader program
	GLuint projectionLoc = glGetUniformLocation(m_ShaderProg->getProgramID(), "projection");
	GLuint modelviewLoc = glGetUniformLocation(m_ShaderProg->getProgramID(), "modelview");

	// Set projection matrix in shader
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(m_Camera->getProjectionMatrix()));

	// Set ModelMatrix for heightmap to identity matrix (no translation/rotation/scale)
	modelMatrix = glm::mat4();

	// Set ModelView matrix in shader
	glUniformMatrix4fv(modelviewLoc, 1, GL_FALSE, glm::value_ptr(m_Camera->getViewMatrix() * modelMatrix));

	// Set heightmap color
	glUniform3fv(m_ShaderProg->getUniformLoc("objectColor"), 1, glm::value_ptr(glm::vec3(0.12f, 0.32f, 0.0f)));

	// Draw heightmap
	m_Heightmap.draw();

	glUseProgram(0);
}

const ShaderProgram* World::getShaderProg() const {
	return m_ShaderProg;
}

Camera* World::getCamera() {
	return m_Camera;
}