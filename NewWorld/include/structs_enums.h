#pragma once


// For Collider and Octree
struct AABB
{
public:
	float xpos, xneg, ypos, yneg, zpos, zneg;
};

// For Motion class
enum Move_Commands_Enum
{
	MOVE_NO_MOVEMENT,
	MOVE_AMPLIFY,
	MOVE_FORWARD,
	MOVE_BACKWARD,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_JUMP,
	MOVE_SHIFT
};


// For Camera class
// Defines several possible options for camera movement.
// Used as abstraction to stay away from window-system specific input methods.
enum Camera_Movement
{
	CAMERA_NO_MOVEMENT,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};