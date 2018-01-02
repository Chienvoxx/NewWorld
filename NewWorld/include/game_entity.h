#ifndef _GAME_ENTITY_
#define _GAME_ENTITY_
#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>


#include <entity_model.h>
#include <entity_position.h>
#include <Motion.h>

class Motion; // Forward declaration


class GameEntity
{
public:
	unsigned int ID;

	/*	
		EntityModel
		ShaderProgram
		Texture(s)
		Location
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
	EntityModel *entityModel;
	Motion motion;

	glm::vec3 origPosition;
	glm::vec3 position;
	glm::vec3 orientation;
	glm::vec3 scale;

	

	GameEntity() {}
	GameEntity(EntityModel *em) {}
	GameEntity(EntityModel *em, glm::vec3 pos) : entityModel(em), position(pos)
	{
		origPosition = position;
	}

	//int setMotion(double maxAccelerationForce, double gravityForce, double accelerationForce, double frictionForce)
	//{
	//	motion.buildMotion(maxAccelerationForce, gravityForce, accelerationForce, frictionForce);
	//}

	void update(Move_Commands command, double time)
	{
		motion.update(command, time);
		position.x += motion.moveVector.x;
		position.y += motion.moveVector.y;
		position.z += motion.moveVector.z;
	}

	void updatePosition(glm::vec3 update)
	{
		origPosition = position;
		position = update;
	}

	void resetPosition()
	{
		position = origPosition;
	}

private:

};

#endif // !_GAME_ENTITY_
