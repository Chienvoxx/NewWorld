#pragma once

#include <map>
#include <vector>
#include <tuple>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <camera.h>
#include <collider.h>
#include <entity_model.h>
#include <game_entity.h>
#include <Motion.h>
#include <timer.h>
#include <chunk.h>

float vertices[] = {
	// positions			// texture coords
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

class World
{
public:
	// the number of chunks that should be drawn each direction from the given loc
	int DRAW_DISTANCE = 2;
	int CHUNK_XZ = 16;
	EntityModel *p_em1;
	GameEntity light;
	GameEntity player;

	World() {}

	void update() {}


	// tuple loc == x,z
	void updateChunks(std::tuple<int, int> loc)
	{
		// get the chunk that loc is in
		int chunkX, chunkZ;
		std::tie(chunkX, chunkZ) = loc;
		chunkX = floor((float)chunkX / (float)CHUNK_XZ);
		chunkZ = floor((float)chunkZ / (float)CHUNK_XZ);

		m_viewableChunkRange.clear();
		// create a list of chunk locations that should be visible
		int halfDistance = (int)DRAW_DISTANCE / 2;
		int beginX = NULL;
		int endX = chunkX + halfDistance;
		int beginZ = NULL;
		int endZ = chunkZ + halfDistance;



		if (DRAW_DISTANCE % 2 == 1)
		{	// odd
			beginZ = chunkZ - (halfDistance + 1);
			beginX = chunkX - (halfDistance + 1);
		}
		else
		{	// even
			beginZ = chunkZ - (halfDistance);
			beginX = chunkX - (halfDistance);
		}

		for (int z = beginZ; z < endZ + 1; z++)
		{
			for (int x = beginX; x < endX + 1; x++)
			{
				m_viewableChunkRange.push_back(std::make_tuple(x, z));
			}
		}

		// check viewable range against viewable chunks and update as needed
		for (auto i : m_viewableChunkRange)
		{
			if (m_viewableChunks.find(i) == m_viewableChunks.end())
			{
				Chunk * c = new Chunk(i, p_em1);
				c->buildLayer(0);
				m_viewableChunks.insert(std::make_pair(i, c));
			}

		}
	}


	std::vector<GameEntity *> getCandidateBlocks(glm::vec3 originatingLocation, int blocksXZ, int blocksY)
	{
		if (originatingLocation.y < -0.3)
			bool test = true;
		std::vector<GameEntity *> candidates = std::vector<GameEntity *>();

		int locX, locY, locZ;
		locX = floor(originatingLocation.x);
		locY = floor(originatingLocation.y);
		locZ = floor(originatingLocation.z);

		int beginOffset, beginX, beginY, beginZ;
		beginOffset = floor(blocksXZ / 2);
		beginX = locX - beginOffset;
		beginY = locY;
		beginZ = locZ - beginOffset;

		for (int y = 0; y < blocksY; y++)
		{
			for (int z = 0; z < blocksXZ; z++)
			{
				for (int x = 0; x < blocksXZ; x++)
				{
					// get the chunk of the location
					int chunkX = (int)floor((float)(beginX + x) / (float)CHUNK_XZ);
					int chunkZ = (int)floor((float)(beginZ + z) / (float)CHUNK_XZ);
					std::tuple<int, int> chunkLoc = std::make_tuple(chunkX, chunkZ);

					// request the block from the chunk
					std::tuple<int, int, int> requestBlock = std::make_tuple(beginX + x, beginY + y, beginZ + z);
					GameEntity * ent = m_viewableChunks.find(chunkLoc)->second->getBlock(requestBlock);
					if(ent != nullptr)
						candidates.push_back(ent);
				}
			}
		}

		return candidates;
	}



	void render(glm::mat4 view, glm::mat4 projection)
	{
		//m_chunk.draw(view, projection);
		for (auto i : m_viewableChunks)
			i.second->draw(view, projection);

		// render a temporary light
		glm::mat4 lightModel;
		lightModel = glm::translate(lightModel, light.position);
		lightModel = glm::scale(lightModel, glm::vec3(1.5f));
		renderLight(lightModel, view, projection);
	}

	void renderLight(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
	{
		light.entityModel->Draw(model, view, projection);
	}

	void renderPlayer(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
	{
		player.entityModel->Draw(model, view, projection);
	}

	void createEntityModel()
	{
		std::vector<float> v(vertices, vertices + sizeof vertices / sizeof vertices[0]);
		p_em1 = new EntityModel("./shaders/Shell.vs", "./shaders/Shell.fs", sizeof vertices, &v);
	}

	void addOneChunk(std::tuple<int, int> loc)
	{
		m_chunk = Chunk(loc, p_em1);
		m_chunk.buildLayer(40);
	}

	//Chunk addChunk(std::tuple<int, int> loc)
	//{
	//	m_chunk = Chunk(glm::vec3(), p_em1);
	//	m_chunk.buildLayer(0);
	//}

	Chunk * chunk()
	{
		//return m_chunk;
		return m_viewableChunks.find(std::make_pair(0, 0))->second;
	}

	void turnLightOn(glm::vec3 pos)
	{
		std::vector<float> v(vertices, vertices + sizeof vertices / sizeof vertices[0]);
		EntityModel *lightModel = new EntityModel("./shaders/Lights.vs", "./shaders/Lights.fs", sizeof vertices, &v);
		
		light = GameEntity(lightModel, pos);
	}

	void createPlayer(glm::vec3 pos)
	{
		std::vector<float> v(vertices, vertices + sizeof vertices / sizeof vertices[0]);
		EntityModel *playerModel = new EntityModel("./shaders/Shell.vs", "./shaders/Shell.fs", sizeof vertices, &v);

		player = GameEntity(playerModel, pos);
	}


private:
	Chunk m_chunk;
	std::vector<std::tuple<int, int>> m_viewableChunkRange;
	std::map<std::tuple<int, int>, Chunk*> m_viewableChunks;

	// models, an array of modelInstances
	// modelInstances, contains model and instance data, and methods to initialize and render.
	// each entity using the model has the ID in a modelId data field.
	// World requests from each chunk data about which blocks need to be drawn
	// Blocks sharing a modelId store their transformations in an array for that ID.
	
};
