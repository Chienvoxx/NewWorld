#pragma once

#ifndef _CHUNK_H
#define _CHUNK_H

#include <vector>
#include <tuple>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <game_entity.h>
#include <entity_model.h>


class Chunk
{
public:
	Chunk() {}
	Chunk(std::tuple<int, int> loc, EntityModel *em) : em1(em)
	{
		int x, z;
		std::tie(x, z) = loc;
		worldLoc = glm::vec3((float)x*CHUNK_XZ, 0.0f, (float)z*CHUNK_XZ);
	}
	~Chunk() {}

	glm::vec3 location()
	{
		return worldLoc;
	}

	void draw(glm::mat4 view, glm::mat4 projection)
	{
		// set the shader, texture & VAO
		std::map<std::tuple<int, int>, GameEntity *> layer = layers.find(0)->second;
		auto it = layer.begin();
		if (it != layer.end())
		{
			//GameEntity * entityType = layer.find(std::make_pair(0, 0))->second;
			GameEntity * entityType = it->second;
			entityType->entityModel->shader.setMat4("view", view);
			entityType->entityModel->shader.setMat4("projection", projection);
			// Binding textures does not need to happen for every draw call
			glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, chunkLayer.at(0)->entityModel->texture1);
			glBindTexture(GL_TEXTURE_2D, entityType->entityModel->texture1);
			glActiveTexture(GL_TEXTURE1);
			//glBindTexture(GL_TEXTURE_2D, chunkLayer.at(0)->entityModel->texture2);
			glBindTexture(GL_TEXTURE_2D, entityType->entityModel->texture2);
			//glBindVertexArray(chunkLayer.at(0)->entityModel->VAO);
			glBindVertexArray(entityType->entityModel->VAO);
		}

		//Draw an array of entity/cube via class abstraction
		for (auto & l : layers)
		{
			for (auto & y : l.second)
			{
				glm::mat4 model;
				model = glm::translate(model, y.second->position);
				model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
				y.second->entityModel->shader.setMat4("model", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}

		//chunkLayer.at(0)->entityModel->shader.setMat4("view", view);
		//chunkLayer.at(0)->entityModel->shader.setMat4("projection", projection);
	}


	void buildLayer(int layerLevel)
	{
		int y = layerLevel;
		//chunkLayer.reserve(CHUNK_XZ * CHUNK_XZ);
		std::map<std::tuple<int, int>, GameEntity *> chunkLayer;

		for (size_t x = 0; x < CHUNK_XZ; x++)
		{	
			for (size_t z = 0; z < CHUNK_XZ; z++)
			{
				std::tuple<int, int> xz = std::make_tuple((int)(worldLoc.x + x), (int)(worldLoc.z + z));
				glm::vec3 pos = glm::vec3(worldLoc.x + (float)x, worldLoc.y + (float)y, worldLoc.z + (float)z);
				GameEntity *ge = new GameEntity(em1, pos);
				chunkLayer.insert(std::make_pair(xz, ge));
			}
		}
		layers.insert(std::make_pair(y, chunkLayer));
	}

	//std::vector<GameEntity *> entitiesVec()
	//{
	//	return chunkLayer;
	//}

	GameEntity * getBlock(std::tuple<int, int, int> loc)
	{
		GameEntity *candidate;

		int locX, locY, locZ;
		std::tie(locX, locY, locZ) = loc;
		int index = (CHUNK_XZ * (locX % CHUNK_XZ)) + (locZ % CHUNK_XZ);
		if (index < 0)
			index *= -1;

		//std::vector<GameEntity *>::iterator it;
		auto y = layers.find(locY);
		if (y != layers.end())
		{
			candidate = y->second.find(std::make_pair(locX, locZ))->second;
			return candidate;
		}
		else
		{
			return nullptr;
		}
	}


private:
	int CHUNK_XZ = 16;
	glm::vec3 worldLoc;
	std::map<int, std::map<std::tuple<int, int>, GameEntity *> > layers;
	//std::map<std::tuple<int, int>, GameEntity *> chunkLayer;
	EntityModel *em1;

};


#endif // !_CHUNK_H

