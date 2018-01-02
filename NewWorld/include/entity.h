#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>


class Entity
{
public:
	unsigned int ID;
	/*	Location
			translation
			rotation
			scale
		collision shapes
			*AABB
			specific collidables
		graphsics data
			*vertices
			*textures
			GL Settings
		Parent AABB
		AI
		Animation
	*/
	glm::vec3 location;
	glm::vec3 rotation;
	glm::vec3 scale;
	Entity() {}

private:
};
