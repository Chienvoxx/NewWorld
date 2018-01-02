#pragma once

#include <glm\glm.hpp>

#ifndef _ENTITY_POSITION_
#define _ENTITY_POSITION_


class EntityPosition
{
public:

	glm::vec3 *position;
	int locX;
	int locY;
	int locZ;
	int chunkX;
	int chunkZ;


	EntityPosition();
	EntityPosition(glm::vec3 *pos);

	// Position is a pointer to the parent GameEntity position
	// Update all variables with current *position values
	void update();

	void addPosition(glm::vec3 *pos);

	~EntityPosition();

private:

};

EntityPosition::EntityPosition(){}

EntityPosition::EntityPosition(glm::vec3 *pos) : position(pos) {}

void EntityPosition::update()
{
	locX = (int)position->x;
	locY = (int)position->y;
	locZ = (int)position->z;
}

void EntityPosition::addPosition(glm::vec3 *pos)
{
	position = pos;
}

EntityPosition::~EntityPosition()
{
	delete position;
}





#endif // !_ENTITY_POSITION_

