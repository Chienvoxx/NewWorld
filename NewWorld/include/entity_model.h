#pragma once

#include <vector>
#include <stb_image\stb_image.h>
#include <shader.h>

class EntityModel
{
public:
	std::vector<float> *vertices;
	std::vector<unsigned int> _indices;
	//std::vector<Texture> _textures;
	int verticesSize;
	//float *vertices;
	int width, height, nrChannels;
	unsigned char *data;
	unsigned int VAO;
	unsigned int texture1;
	unsigned int texture2;
	Shader shader;


	EntityModel();
	EntityModel(const char* vertexPath, const char* fragmentPath, unsigned int vertSize, std::vector<float> *vert);
	unsigned int loadTextureRGB(const char *filename);
	unsigned int loadTextureRGBA(const char *filename);
	void Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
	void Draw(Shader shader);

private:
	unsigned int VBO, EBO;
};
