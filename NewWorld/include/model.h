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


class Model
{
public:

	std::vector<Mesh> meshes;

	Model(const char *file) 
	{
		buildModel(file);
	}

	Mesh processFile(std::vector<std::string> &lines);

private:

	void buildModel(const char *file);


};
#endif // !_MODEL_H

void Model::buildModel(const char *file)
{
	std::vector<std::string> lines = readTextFileLines(file);
	processFile(lines);

}

Mesh Model::processFile(std::vector<std::string> &lines)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	std::vector<unsigned int> temp_Indices;
	std::vector<glm::vec3> temp_Vertices;
	std::vector<glm::vec3> temp_Normals;
	std::vector<glm::vec2> temp_UVs;

	for (auto & s : lines)
	{
		std::istringstream iss(s);
		std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };

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
			vt.x = (float)atof(tokens.at(1).c_str());
			vt.y = (float)atof(tokens.at(2).c_str());
			temp_UVs.push_back(vt);
		}
		if (tokens.at(0) == "vn")
		{
			glm::vec3 n;
			n.x = (float)atof(tokens.at(1).c_str());
			n.y = (float)atof(tokens.at(2).c_str());
			n.z = (float)atof(tokens.at(3).c_str());
			temp_Normals.push_back(n);
		}
		if (tokens.at(0) == "f")
		{

		}

	}

	return Mesh(vertices, indices, textures);
}

