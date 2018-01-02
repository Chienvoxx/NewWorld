#include <entity_model.h>
//float p_vertices[] = {
//	// positions			// texture coords
//	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
//	0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
//	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
//	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
//	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
//
//	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
//	0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
//	0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
//	0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
//	-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
//
//	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
//
//	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
//	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
//	0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
//	0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
//	0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
//	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
//
//	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
//	0.5f, -0.5f, -0.5f,		1.0f, 1.0f,
//	0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
//	0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
//	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
//	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
//
//	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
//	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
//	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
//	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f
//};

float p_vertices[] = {
	// CCW Winding
	// positions			// texture coords
	// Back face
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
	// Front face
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
	// Left face
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
	// Right face
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
	// Bottom face
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
	// Top face
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left
};

float p_vertices2[] = {
	0.5f,	-0.5f,	-0.5f, // right	bottom	front
	0.5f,	-0.5f,	 0.5f, // right	bottom	back
	-0.5f,	-0.5f,	 0.5f, // left	bottom	back
	-0.5f,	-0.5f,	-0.5f, // left	bottom	front
	0.5f,	 0.5f,	-0.5f, // right	top		front
	0.5f,	 0.5f,	 0.5f, // right	top		back
	-0.5f,	 0.5f,	 0.5f, // left	top		back
	-0.5f,	 0.5f,	-0.5f  // left	top		front
};




unsigned int indices[] = {
	0, 1, 2, // Bottom
	0, 2, 3, // 
	4, 7, 6, // Top

};

/*
	const std::vector<float> vertices;
	int width, height, nrChannels;
	unsigned char *data;
	unsigned int VBO, VAO, EBO;
	unsigned int texture1;
	unsigned int texture2;
	Shader mShader;
*/
EntityModel::EntityModel() {}
EntityModel::EntityModel(const char* vShaderPath, const char* fShaderPath, unsigned int vertSize, std::vector<float> *vert)
	: verticesSize(vertSize)
{
	vertices = vert;
	int s = vertices->size();
	// build and compile our shader program
	// ------------------------------------
	shader = Shader(vShaderPath, fShaderPath);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(p_vertices) , p_vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	texture1 = loadTextureRGB("./images/container.jpg");
	texture2 = loadTextureRGBA("./images/awesomeface.png");
	shader.use();
	glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0); //set it manually
	shader.setInt("texture2", 1); // or with shader class

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

unsigned int EntityModel::loadTextureRGB(const char *filename)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		stbi_image_free(data);
		return 0;
	}

	stbi_image_free(data);
	return texture;
}

unsigned int EntityModel::loadTextureRGBA(const char *filename)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		stbi_image_free(data);
		return 0;
	}

	stbi_image_free(data);
	return texture;
}

void EntityModel::Draw(Shader shader)
{
	shader.use();
	glActiveTexture(GL_TEXTURE0);

	// Draw mesh
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void EntityModel::Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	//GameEntity * entityType = layer.find(std::make_pair(0, 0))->second;
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	// Binding textures does not need to happen for every draw call
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glBindVertexArray(VAO);

	// Draw mesh
	shader.setMat4("model", model);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}