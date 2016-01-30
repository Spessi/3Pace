#include "World.h"

World::World() {
}

World::~World() {
	delete m_ShaderProg;
}

GLuint World::loadCube() {
	GLuint gVAO = 0;
	GLuint gVBO = 0;
	GLuint gIVBO = 0;

	// make and bind the VAO
	glGenVertexArrays(1, &gVAO);
	glBindVertexArray(gVAO);


	// Put the three triangle verticies into the VBO (3*float Vertex, 3* float Normal)
	GLfloat vertexData[] = {
		// Bottom
		-5.0f, -5.0f, 5.0f,
		0.0f, -1.0f, 0.0f,
		5.0f, -5.0f, 5.0f,
		0.0f, -1.0f, 0.0f,
		5.0f, -5.0f, -5.0f,
		0.0f, -1.0f, 0.0f,
		-5.0f, -5.0f, -5.0f,
		0.0f, -1.0f, 0.0f,

		// Back
		-5.0f, 5.0f, 5.0f,
		0.0f, 0.0f, 1.0f,
		5.0f, 5.0f, 5.0f,
		0.0f, 0.0f, 1.0f,

		// Front
		-5.0f, 5.0f, -5.0f,
		0.0f, 0.0f, -1.0f,
		5.0f, 5.0f, -5.0f,
		0.0f, 0.0f, -1.0f,

		// Left
		-5.0f, 5.0f, 5.0f,
		-1.0f, 0.0f, 0.0f,
		-5.0f, 5.0f, -5.0f,
		-1.0f, 0.0f, 0.0f,

		// Right
		5.0f, 5.0f, 5.0f,
		1.0f, 0.0f, 0.0f,
		5.0f, 5.0f, -5.0f,
		1.0f, 0.0f, 0.0f,

		// Top
		-5.0f, 5.0f, -5.0f,
		0.0f, 1.0f, 0.0f,
		5.0f, 5.0f, -5.0f,
		0.0f, 1.0f, 0.0f,
		5.0f, 5.0f, 5.0f,
		0.0f, 1.0f, 0.0f,
		-5.0f, 5.0f, 5.0f,
		0.0f, 1.0f, 0.0f,
	};

	GLuint indexData[] = {
		// Bottom
		0, 2, 3,
		0, 1, 2,

		// Back
		0, 1, 4,
		1, 5, 4,

		// Front
		3, 6, 7,
		3, 7, 2,

		// Left
		3, 8, 9,
		3, 0, 8,

		// Right
		1, 2, 11,
		1, 11, 10,

		// Top
		12, 15, 14,
		12, 14, 13,
	};


	// make and bind the VBO
	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData) * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);
	// connect the xyz to the "vert" attribute of the vertex shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// Load normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	// Create Vertex Buffer Object for the indices and bind it
	glGenBuffers(1, &gIVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIVBO);
	// Upload the indices to the VBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData) * sizeof(GLuint), &indexData, GL_STATIC_DRAW);



	// unbind the VBO and VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return gVAO;
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


	m_EntityMgr = new EntityManager();
	unsigned int id = -1;

	std::cout << "Create Entity: " << (id = m_EntityMgr->createEntity()) << std::endl;
	std::cout << "Add PositionComponent to Entity " << id << "!" << std::endl;
	m_EntityMgr->addComponent(id, new PositionComponent(glm::vec3(0.0f, 45.0f, 00.0f)));
	std::cout << "Add VelocityComponent to Entity " << id << "!" << std::endl;
	m_EntityMgr->addComponent(id, new VelocityComponent(20.0, 120.0f));
	std::cout << "Add MeshComponent to Entity " << id << "!" << std::endl;
	m_EntityMgr->addComponent(id, new IntentComponent());
	m_EntityMgr->addComponent(id, new MeshComponent(loadCube(), 36, glm::vec3(0.26f, 0.82f, 0.2f)));

	// Heightmap
	Heightmap heightmap;
	heightmap.loadFromFile("heightmap.png");
	id = m_EntityMgr->createEntity();
	m_EntityMgr->addComponent(id, new PositionComponent);
	m_EntityMgr->addComponent(id, new MeshComponent(heightmap.getVAO(), heightmap.getVerticesCount(), glm::vec3(0.46f, 0.32f, 0.2f)));


	// CAMERA 1
	std::cout << "Creating Camera..." << std::endl;
	std::cout << "Create Entity: " << (id = m_EntityMgr->createEntity()) << std::endl;
	std::cout << "Add PositionComponent to Entity " << id << "!" << std::endl;
	m_EntityMgr->addComponent(id, new PositionComponent(glm::vec3(0.0f, 45.0f, 15.0f)));
	std::cout << "Add CameraComponent to Entity " << id << "!" << std::endl;
	m_EntityMgr->addComponent(id, new CameraComponent());

	 
	m_SystemMgr = new SystemManager();
	m_SystemMgr->registerSystem(new InputSystem());
	m_SystemMgr->registerSystem(new PhysicsSystem());
	m_CameraSystem = new CameraSystem(m_EntityMgr);
	m_SystemMgr->registerSystem(m_CameraSystem);
	m_SystemMgr->registerSystem(new RenderSystem(m_CameraSystem, m_ShaderProg));



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


	// Process Entity Component System
	m_SystemMgr->process(m_EntityMgr->getEntities(), m_Delta);
	//render();
	return;
	/*
	// TODO: auslagern
	{
		if (m_CameraSystem->getActiveCamera() == nullptr)
			return;
		glm::mat4 modelMatrix;
		// bind the program (the shaders)
		glUseProgram(m_ShaderProg->getProgramID());	
		// Transform light position (0/100/0) into ModelView space
		glm::vec3 lightPos = glm::vec3(m_CameraSystem->getActiveCamera()->getViewMatrix() * modelMatrix * glm::vec4(0.0f, 100.0f, 0.0f, 1.0f));
		glUniform3fv(m_ShaderProg->getUniformLoc("lightPos"), 1, glm::value_ptr(lightPos));


		// Get the ModelViewProjection-PropertyID from the shader program
		GLuint projectionLoc = glGetUniformLocation(m_ShaderProg->getProgramID(), "projection");
		GLuint modelviewLoc = glGetUniformLocation(m_ShaderProg->getProgramID(), "modelview");

		// Set projection matrix in shader
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(m_CameraSystem->getActiveCamera()->getProjectionMatrix()));
	}



	// TODO: auslagern
	{
		glUseProgram(0);
	}*/

	// Render
	//render();
	// Render End
}

void World::render() {
	glm::mat4 modelMatrix;
	static float angle = 0.0f;
	

	// bind the program (the shaders)
	glUseProgram(m_ShaderProg->getProgramID());




	if (m_CameraSystem->getActiveCamera() == nullptr) {
		return;
	}

	// Transform light position (0/100/0) into ModelView space
	glm::vec3 lightPos = glm::vec3(m_CameraSystem->getActiveCamera()->getViewMatrix() * modelMatrix * glm::vec4(0.0f, 100.0f, 0.0f, 1.0f));
	glUniform3fv(m_ShaderProg->getUniformLoc("lightPos"), 1, glm::value_ptr(lightPos));


	// Get the ModelViewProjection-PropertyID from the shader program
	GLuint projectionLoc = glGetUniformLocation(m_ShaderProg->getProgramID(), "projection");
	GLuint modelviewLoc = glGetUniformLocation(m_ShaderProg->getProgramID(), "modelview");

	// Set projection matrix in shader
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(m_CameraSystem->getActiveCamera()->getProjectionMatrix()));

	// Render Heightmap
	{
		// Set ModelMatrix for heightmap to identity matrix (no translation/rotation/scale)
		modelMatrix = glm::mat4();
		// Set ModelView matrix in shader
		glUniformMatrix4fv(modelviewLoc, 1, GL_FALSE, glm::value_ptr(m_CameraSystem->getActiveCamera()->getViewMatrix() * modelMatrix));
		// Set heightmap color
		glUniform3fv(m_ShaderProg->getUniformLoc("objectColor"), 1, glm::value_ptr(glm::vec3(0.12f, 0.32f, 0.0f)));
		// Draw heightmap
		//m_Heightmap.draw();
	}


	glUseProgram(0);
}

const ShaderProgram* World::getShaderProg() const {
	return m_ShaderProg;
}