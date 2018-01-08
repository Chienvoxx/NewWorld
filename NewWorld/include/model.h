#pragma once
#ifndef _MODEL_H
#define _MODEL_H

//#include <mesh.h>
#include <utils.h>

#include <glm\glm.hpp>

//#include <vector>
//#include <iostream>
//#include <string>
//#include <sstream>
//#include <algorithm>
#include <iterator>


/*
	Modle class is strictly written to parse a .obj file into a model
	At first run 1/7/2018, it will only load a cube object
	It reads the vertex and face data, builds vertexes and indices,
		Opens the .mtl file
			finds the name of the diffuse image image_name.png
			loads that image
*/

class Model
{
public:

	std::vector<Mesh> meshes;

	Model(const char *path, const char *folder);


private:
	const char *mPath;
	const char *mFileName;
	std::vector<glm::vec3> mVertices;
	std::vector<glm::vec3> mNormals;
	std::vector<glm::vec2> mUVs;
	std::vector<unsigned int> faces;


	void buildModel();
	void parseObjFile();
	void parseMtlFile();
	void processMtlFile(std::vector<std::string> &lines);
	Mesh processObjFile(std::vector<std::string> &lines);
	int readMeterialFile(std::string filename, std::string type);


};
#endif // !_MODEL_H

Model::Model(const char *path, const char *fileName) : mPath(path), mFileName(fileName)
{
	buildModel();
}

void Model::buildModel()
{
	// read image - create texture;
	parseMtlFile();

	parseObjFile();
}

void Model::parseMtlFile()
{
	std::string mtlFile = mPath;
	mtlFile += mFileName;
	mtlFile += ".mtl";
	//readTextFileLines in util.h
	std::vector<std::string> lines = readTextFileLines(mtlFile.c_str());
	processMtlFile(lines);
}



void Model::parseObjFile()
{
	std::string objFile = mPath;
	objFile += mFileName;
	objFile += ".obj";
	//readTextFileLines in util.h
	std::vector<std::string> lines = readTextFileLines(objFile.c_str());
	processObjFile(lines);
}

void Model::processMtlFile(std::vector<std::string> &lines)
{
	for (auto & s : lines)
	{
		std::vector<std::string> tokens = tokenize(s, ' ');

		if (tokens.size() > 0)
		{
			if (tokens.at(0) == "map_Kd")
			{
				std::string filename = mPath;
				filename += tokens.at(1);
				readMeterialFile(filename, "texture_diffuse");
			}
			if (tokens.at(0) == "map_Ks") // not verified
			{
				std::string filename = mPath;
				filename += tokens.at(1);
				readMeterialFile(filename, "texture_specular");
			}
			if (tokens.at(0) == "map_Kn") // not verified
			{
				std::string filename = mPath;
				filename += tokens.at(1);
				readMeterialFile(filename, "texture_normal");
			}
			if (tokens.at(0) == "map_Kh") // not verified
			{
				std::string filename = mPath;
				filename += tokens.at(1);
				readMeterialFile(filename, "texture_height");
			}
		}
	}
}

int Model::readMeterialFile(std::string filename, std::string type)
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
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
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
}


Mesh Model::processObjFile(std::vector<std::string> &lines)
{ // lines contains each line of an .obj file
	
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_Vertices;
	std::vector<glm::vec3> temp_Normals;
	std::vector<glm::vec2> temp_UVs;
	unsigned int vertex_count = 0;

	char *result;
	for (auto & s : lines)
	{
		std::istringstream iss(s);
		std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };

		if (tokens.size() > 0)
		{
			if (tokens.at(0) == "v")
			{
				glm::vec3 v;
				v.x = strtof(tokens.at(1).c_str(), nullptr);
				v.y = strtof(tokens.at(2).c_str(), nullptr);
				v.z = strtof(tokens.at(3).c_str(), nullptr);
				temp_Vertices.push_back(v);
			}
			if (tokens.at(0) == "vt")
			{
				glm::vec2 vt;
				vt.x = strtof(tokens.at(1).c_str(), nullptr);
				vt.y = strtof(tokens.at(2).c_str(), nullptr);
				temp_UVs.push_back(vt);
			}
			if (tokens.at(0) == "vn")
			{
				glm::vec3 n;
				n.x = strtof(tokens.at(1).c_str(), nullptr);
				n.y = strtof(tokens.at(2).c_str(), nullptr);
				n.z = strtof(tokens.at(3).c_str(), nullptr);
				temp_Normals.push_back(n);
			}
			if (tokens.at(0) == "f")
		{ // a face
			for (auto s : tokens)
			{	// Example: if tokens == {"f","1/1/1","2/2/1","3/3/1","4/4/1"}
				// s will == "1/1/1" then "2/2/1", etc.
				if (s != "f")
				{	// vi is the individual vertex attribute of the face
					// if s == "2/2/1"
					// vi will == {"2","2","1"}
					std::vector<std::string> vi = tokenize(s, '/'); // tokkenize is in utils.h
					vertexIndices.push_back(atoi(vi.at(0).c_str()));
					uvIndices.push_back(atoi(vi.at(1).c_str()));
					normalIndices.push_back(atoi(vi.at(2).c_str()));
				}
			}
			if (tokens.size() == 4)
			{	// case: face is a single triangle
				
				// groups are assumed to be CCW
				// triangles are (1,2,3)
				indices.push_back(vertex_count + 1);
				indices.push_back(vertex_count + 2);
				indices.push_back(vertex_count + 3);

				// increment vertex_count for the next face
				vertex_count += 3;
			}
			if (tokens.size() == 5)
			{	// case: face is a rectangle consiting of two triangles
				
				// groups are assumed to be CCW
				// triangles are (1,2,3) and (3,4,1)
				indices.push_back(vertex_count + 1);
				indices.push_back(vertex_count + 2);
				indices.push_back(vertex_count + 3);

				indices.push_back(vertex_count + 3);
				indices.push_back(vertex_count + 4);
				indices.push_back(vertex_count + 1);

				// increment vertex_count for the next face
				vertex_count += 4;
			}
		}
		}
	}

	// using indices, assemble vertex data in correct order
	for (unsigned int i = 0; i < vertexIndices.size(); i ++ )
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_Vertices[vertexIndex - 1];
		mVertices.push_back(vertex);

		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_UVs[uvIndex - 1];
		mUVs.push_back(uv);

		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_Normals[normalIndex - 1];
		mNormals.push_back(normal);

		// create the Vertex
		Vertex v;
		v.Position = vertex;
		v.TexCoords = uv;
		v.Normal = normal;
		vertices.push_back(v);
	}

	// create indices

	//return Mesh();
	return Mesh(vertices, indices, textures);
}

