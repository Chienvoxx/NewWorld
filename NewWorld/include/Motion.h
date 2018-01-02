#ifndef _MOTION_
#define _MOTION_

#pragma once

#include <structs_enums.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>


class GameEntity;

//enum Move_Commands_Enum
//{
//	MOVE_NO_MOVEMENT,
//	MOVE_AMPLIFY,
//	MOVE_FORWARD,
//	MOVE_BACKWARD,
//	MOVE_LEFT,
//	MOVE_RIGHT,
//	MOVE_UP,
//	MOVE_DOWN,
//	MOVE_JUMP,
//	MOVE_SHIFT
//};

struct Move_Commands
{
	bool MOVE_NO_MOVEMENT = false;
	bool MOVE_AMPLIFY = false;
	bool MOVE_FORWARD = false;
	bool MOVE_BACKWARD = false;
	bool MOVE_LEFT = false;
	bool MOVE_RIGHT = false;
	bool MOVE_UP = false;
	bool MOVE_DOWN = false;
	bool MOVE_JUMP = false;
	bool MOVE_SHIFT = false;
};

struct Motion_State
{
	double x;
	double y;
	double z;
} motionState;

class Motion
{
public:
	double MAX_ACCELERATION;
	double MAX_GRAVITY_ACCELERATION;
	double gravity = 0.0;
	double acceleration;
	double friction;

	glm::vec3 moveVector;

	double inertia;
	glm::vec3 lookDirection;


	Motion() {}
	//Motion(GameEntity *parent, double maxAccelerationForce, double gravityForce, double accelerationForce, double frictionForce) :
	//	mp_parent(parent),
	//	MAX_ACCELERATION(maxAccelerationForce),
	//	gravity(gravityForce),
	//	acceleration(accelerationForce),
	//	friction(frictionForce)
	//{}

	void buildMotion(double gravityForce, double accelerationForce, double frictionForce, double maxAccelerationForce)
	{
		gravity = gravityForce;
		acceleration = accelerationForce;
		friction = frictionForce;
		MAX_ACCELERATION = maxAccelerationForce;
		MAX_GRAVITY_ACCELERATION = 9 * MAX_ACCELERATION;
		moveVector = glm::vec3(0.0);
	}


	void update(Move_Commands commands, double time)
	{
		if (commands.MOVE_BACKWARD)
			bool debug = true;
		if (commands.MOVE_FORWARD)
			bool debug = true;

		double accelByTime = acceleration * time;
		double maxAccelByTime = MAX_ACCELERATION * time;
		double maxGravityAccelByTime = MAX_GRAVITY_ACCELERATION * time;
		double gravityByTime = gravity * time;
		double frictionByTime = friction * time;
		m_moveCommands = commands;
		//moveVector = glm::vec3(0.0);
		double fb=0.0, lr=0.0, ud=0.0;
		float *x = &moveVector.x;
		float *y = &moveVector.y;
		float *z = &moveVector.z;

		lr += m_moveCommands.MOVE_LEFT * accelByTime * -1;
		lr += m_moveCommands.MOVE_RIGHT * accelByTime;

		ud += m_moveCommands.MOVE_UP * gravityByTime;
		ud += gravityByTime * -1;
		
		fb += m_moveCommands.MOVE_FORWARD * accelByTime * -1;
		fb += m_moveCommands.MOVE_BACKWARD * accelByTime;

		moveVector += glm::vec3(lr, ud, fb);
		
		// friction
		if (*x != 0.0f)
		{
			if (*x > 0.0f)
			{
				if (*x <= frictionByTime)
				{
					*x = 0.0f;
				}
				else if (*x > frictionByTime)
				{
					*x -= frictionByTime;
				}
				if (*x > maxAccelByTime)
					*x = maxAccelByTime;
			}
			if (*x < 0.0f)
			{
				if (*x >= 1-frictionByTime)
				{
					*x = 0.0f;
				}
				else if (*x < frictionByTime)
				{
					*x += frictionByTime;
				}
				if (*x < maxAccelByTime*-1)
					*x = maxAccelByTime*-1;
			}
		}
		if (*y != 0.0f)
		{
			if (*y > 0.0f)
			{
				if (*y <= frictionByTime)
				{
					*y = 0.0f;
				}
				else if (*y > frictionByTime)
				{
					*y -= frictionByTime;
				}
				if (*y > maxAccelByTime)
					*y = maxAccelByTime;
			}
			if (*y < 0.0f)
			{
				if (*y >= 1-frictionByTime/10)
				{
					*y = 0.0f;
				}
				else if (*y < frictionByTime/10*-1)
				{
					*y += frictionByTime/10;
				}
				if (*y < maxGravityAccelByTime*-1)
					*y = maxGravityAccelByTime*-1;
			}
		}
		if (*z != 0.0f)
		{
			if (*z > 0.0f)
			{
				if (*z <= frictionByTime)
				{
					*z = 0.0f;
				}
				else if (*z > frictionByTime)
				{
					*z -= frictionByTime;
				}
				if (*z > maxAccelByTime)
					*z = maxAccelByTime;
			}
			if (*z < 0.0f)
			{
				if (*z >= 1-frictionByTime)
				{
					*z = 0.0f;
				}
				else if (*z < frictionByTime)
				{
					*z += frictionByTime;
				}
				if (*z < maxAccelByTime*-1)
					*z = maxAccelByTime*-1;
			}
		}
		
	}

private:
	Move_Commands m_moveCommands;
	GameEntity *mp_parent;
};

#endif // !_MOTION_