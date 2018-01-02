#pragma once

#include <game_entity.h>

#include <vector>



class Octnode
{
public:


private:

	Octnode	*parent;
	std::vector<Octnode> children;
	std::vector<GameEntity> otherBBsList;

	std::vector<GameEntity> sortList
};
