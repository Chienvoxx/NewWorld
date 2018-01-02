#pragma once
#include <game_entity.h>
#include <structs_enums.h>

#include <vector>



class Collider
{
public:
	bool TEST_BREAK = false;

	double epsilon = 0.001;
	// The item to test for collision
	GameEntity *subject;
	// Items to test subject against
	std::vector<GameEntity*> gameEntyties;
	//Collider() {}
	//Collider(GameEntity *subject) {}
	//Collider(std::vector<GameEntity*> candidates) {}
	Collider(GameEntity *subject, std::vector<GameEntity*> candidates) : subject(subject), gameEntyties(candidates)
	{
		subjectBb = createAABB(subject->position, 1.0f);
		for (std::vector<GameEntity*>::iterator it = gameEntyties.begin(); it != gameEntyties.end(); ++it)
		{
			candidatesBb.push_back(createAABB((*it)->position, 1.0f));
		}
	}
	
	// Create bounding box from positions
	// Values are x, -x, y, -y, z, -z
	AABB createAABB(glm::vec3 pos, float scale)
	{
		AABB bb;
		float adjustedScale = scale - epsilon;
		bb.xpos = (pos.x + (0.5 * adjustedScale));
		bb.xneg = (pos.x - (0.5 * adjustedScale));
		bb.ypos = (pos.y + (0.5 * adjustedScale));
		bb.yneg = (pos.y - (0.5 * adjustedScale));
		bb.zpos = (pos.z + (0.5 * adjustedScale));
		bb.zneg = (pos.z - (0.5 * adjustedScale));

		return bb;
	}

	void update()
	{
		if (TEST_BREAK)
			TEST_BREAK = false;
		// test sub against each candidate
		// if a collision is detected return oldPosition
		// if no collition return newPosition
		bool xHit = false;
		bool yHit = false;
		bool zHit = false;
		

		for (std::vector<AABB>::iterator it = candidatesBb.begin(); it != candidatesBb.end(); ++it)
		{
			if (aabbCollision(subjectBb, *it))
			{
				// move as much as possible in any direction
				glm::vec3 incrementPosition = subject->origPosition;

				glm::vec3 moveVec = subject->position - subject->origPosition;
				glm::vec3 deltaX = glm::vec3(moveVec.x, 0.0, 0.0);
				glm::vec3 deltaY = glm::vec3(0.0, moveVec.y, 0.0);
				glm::vec3 deltaZ = glm::vec3(0.0, 0.0, moveVec.z);
				glm::vec3 moveX = subject->origPosition + deltaX;
				glm::vec3 moveY = subject->origPosition + deltaY;
				glm::vec3 moveZ = subject->origPosition + deltaZ;
				AABB xB = createAABB(moveX, 1.0);
				AABB yB = createAABB(moveY, 1.0);
				AABB zB = createAABB(moveZ, 1.0);

				if (!aabbCollision(xB, *it))
				{
					incrementPosition += deltaX;
				}
				else
				{
					// resolveCollision(axis, subjectBB, candidateBB)
					deltaX.x = resolveCollision(1, xB, *it);
					incrementPosition += deltaX;
					subject->motion.moveVector.x = 0.0;
				}
				if (!aabbCollision(yB, *it))
				{
					incrementPosition += deltaY;
				}
				else
				{
					// resolveCollision(axis, subjectBB, candidateBB)
					deltaY.y = resolveCollision(1, yB, *it);
					incrementPosition += deltaY;
					subject->motion.moveVector.y = 0.0;
				}
				if (!aabbCollision(zB, *it))
				{
					incrementPosition += deltaZ;
				}
				else
				{
					// resolveCollision(axis, subjectBB, candidateBB)
					deltaZ.z = resolveCollision(1, zB, *it);
					incrementPosition += deltaZ;
					subject->motion.moveVector.z = 0.0;
				}
				subject->position = incrementPosition;
			}
		}
	}

	// ------------------
	// Resolves collision for the axis given 
	// xyzAxis 0==x, 1==y, 2==z
	double resolveCollision(int xyzAxis, AABB subjBB, AABB candidateBB)
	{
		//	epsilon	e	0.001


		//			a-b-e		 1.999	 0.999	 0.999
		//	up		a-b			 2		 1		 1			increase / movement postive

		//	a		a			 1		-2		 3
		//	b		b			-1		-3		 2

		//	down	b-a			-2		-1		-1			decrease / negative movement
		//			b-a+e		-1.999	-0.999	-0.999
		
		glm::vec4 boundingPlanes;
		AABB from = createAABB(subject->origPosition, 1.0);
		AABB to = subjBB;
		AABB can = candidateBB;

		// Most collisions will be along the y axis due to gravity
		if(xyzAxis == 1)
		{
			// do y axis stuff
			// moving down, diff = bottom - top
			if (from.yneg > can.ypos && to.yneg < can.ypos)
			{
				// b-a+e
				return can.ypos - from.yneg + epsilon;
			}
			// moving up, diff = top - bottom
			else if (from.ypos < can.yneg && to.ypos > can.yneg)
			{
				// a-b-e
				return from.ypos - can.yneg - epsilon;
			}
		}
		else if (xyzAxis == 0)
		{
			// do x axis stuff
			// moving left, diff = left - right
			if (from.xneg > can.xpos && to.xneg < can.xpos)
			{
				// b-a+e
				return can.xpos - from.xneg + epsilon;
			}
			// moving right, diff = right - left
			else if (from.xpos < can.xneg && to.xpos > can.xneg)
			{
				// a-b-e
				return from.xpos - can.xneg - epsilon;
			}
		}
		else if (xyzAxis == 2)
		{
			// do z axis stuff
			// z- faces forward
			// moving forward, diff = front - back
			if (from.zneg > can.zpos && to.zneg < can.zpos)
			{
				// b-a+e
				return can.zpos - from.zneg + epsilon;
			}
			// moving backward, diff = back - front
			else if (from.zpos < can.zneg && to.zpos > can.zneg)
			{
				// a-b-e
				return from.zpos - can.zneg - epsilon;
			}
		}

		// no movement resolved
		return 0.0;
	}
	
	bool aabbCollision(AABB subject, AABB candidate)
	{
		bool xHit = false;
		bool yHit = false;
		bool zHit = false;


		//	case							result
		//	s.x+ < c.x-						no
		//	s.x- > c.x+						no
		//	s.x+ >= c.x- AND s.x- <= c.x+	Possible collision
		//	s.z+ < c.z-						no
		//	s.z- > c.z+						no
		//	s.z+ >= c.z- AND s.z- <= c.z+	Possible collision
		//	s.y+ < c.y-						no
		//	s.y- > c.y+						no
		//	s.y+ >= c.y- AND s.y- <= c.y+	Possible collision

		if (subject.xpos < candidate.xneg ||
			subject.xneg > candidate.xpos ||
			subject.zpos < candidate.zneg ||
			subject.zneg > candidate.zpos ||
			subject.ypos < candidate.yneg ||
			subject.yneg > candidate.ypos )
		{
			return false;
		}

		if (subject.xpos > candidate.xneg && subject.xneg < candidate.xpos)
		{
			xHit = true;
		}
		if (subject.zpos > candidate.zneg && subject.zneg < candidate.zpos)
		{
			zHit = true;
		}
		if (subject.ypos > candidate.yneg && subject.yneg < candidate.ypos)
		{
			yHit = true;
		}

		if (xHit && zHit && yHit)
		{
			return true;
		}
		return false;
	}

private:
	AABB subjectBb;
	std::vector<AABB> candidatesBb;
};
