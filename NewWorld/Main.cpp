#pragma once

#include <iostream>
#include <filesystem>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <sqlite3.h>
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION

#include <camera.h>
#include <collider.h>
#include <entity_position.h>
#include <entity_model.h>
#include <game_entity.h>
#include <Motion.h>
#include <shader.h>
#include <timer.h>
#include <world.h>
#include <model.h>
#include <utils.h>

namespace fs = std::experimental::filesystem;

//Assimp::Importer importer;
Move_Commands processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

GLFWwindow* window;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
unsigned int screenWidth = 0;
unsigned int screenHeight = 0;

// world
World world;

// mouse
float lastX, lastY;
float yaw = -90.0;
float pitch = -15.0;
float fov = 45.0f;
bool firstMouse = true;
bool mouse_move = false;

// Time (scale, start, pause)
Timer timer(1.0, false, false);

double deltaTime = 0.0;
double deltaTicks = 0.0;
double lastTime = 0.0;
double fpsTimer = 0.0;
int fpsCount = 0;

glm::vec3 cameraPos = glm::vec3(0.0f, 10.0f, 18.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
Camera camera(cameraPos, cameraUp, yaw, pitch);

GameEntity *gameEntity;
EntityPosition *playerPosition;

bool DRAW_ARRAY = true;
bool TEST_BREAK = false;
const float MOVE_SPEED = 0.001f;

float vertices2[] = {
	// positions			// texture coords
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,		1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f
};

int initWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfw window creation
	// --------------------
	screenWidth = SCR_WIDTH;
	screenHeight = SCR_HEIGHT;
	lastX = (float)screenWidth / 2;
	lastY = (float)screenHeight / 2;
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	mouse_move = false;
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);


	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	return 0;
}


int main()
{
	if (initWindow() != 0)
	{
		std::cout << "failed to initialize!" << std::endl;
		return -1;
	}
	
	//init sqlite
	sqlite3 *db;
	int rc;
	rc = sqlite3_open("filesys", &db);
	if (rc)
	{
		std::cout << "Can't open database: filesys/n" << sqlite3_errmsg(db);
		sqlite3_close(db);
		return -1;
	}


	glEnable(GL_DEPTH_TEST);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	//float vertices[] = {
	//	// positions          // colors           // texture coords
	//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
	//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	//};
	//unsigned int indices[] = {
	//	0, 1, 3, // first triangle
	//	1, 2, 3  // second triangle
	//};

	world.createEntityModel();
	//world.addOneChunk(std::make_tuple(0, 0));
	world.updateChunks(std::make_tuple(0, 0));

	std::vector<float> v(worldCubeVertices, worldCubeVertices + sizeof worldCubeVertices / sizeof vertices2[0]);
	EntityModel em1("./shaders/Shell.vs", "./shaders/Shell.fs", sizeof vertices2, &v);

	// Set up a single entity/cube via class abstraction
	glm::vec3 playerStart = glm::vec3(0.0f, 30.0f, 0.0f);
	gameEntity = new GameEntity(&em1, playerStart);
	playerPosition = new EntityPosition(&gameEntity->position);
	//playerPosition->addPosition(&gameEntity->position);


	// Acceleration
	double acc = 9.8;
	double gravity = 9.8;
	// buildMotion(gravity, acceleration, friction, MAX_ACCELERATION)
	gameEntity->motion.buildMotion(gravity, acc, acc/6, acc/3);


	// Face culling has to be disabled to render thinkgs like grass
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	timer.start();
	timer.scaleTime(1.0);
	float currentTime = timer.getTime();
	float lastTime = currentTime;
	fpsTimer = currentTime;

	std::vector<glm::vec3> nerest9BlocksPositions;
	std::vector<GameEntity *> nerest9Blocks;

	fs::path p = "models/Grass Free/Blends/Grass.blend";

	//std::cout << fs::current_path() << std::endl;
	//std::cout << fs::system_complete(p) << std::endl;

	world.turnLightOn(glm::vec3(3.0f, 4.0f, -1.0f));
	world.createPlayer(glm::vec3(-4.0f, 6.0f, 0.0f));


	//Model ourModel(fs::absolute("models/cube_uv/cube_uv.blend").string());
	//perror("error state after instaniating model");
	//Shader ourShader("./shaders/Shader_Diffuse.vs", "./shaders/Shader_Diffuse.fs");
	//perror("error state after loading shaders");

	//std::vector<std::string> lines = readTextFileLines("./models/cube_uv/cube_uv.obj");
	//std::vector<std::string> lines = readTextFileLines("./models/cube_uv/cube_uv.obj");

	Model ourModel("./models/cube_uv/cube_uv.obj");


	// game loop
	while (!glfwWindowShouldClose(window))
	{
		// ensure the break boolean is only active once
		TEST_BREAK = false;
		
		// track time
		currentTime = timer.getTime();
		deltaTime = currentTime - lastTime;
		fpsTimer += deltaTime;
		//Sleep(100 - (DWORD)deltaTime);
		lastTime = currentTime;

		deltaTicks = timer.getTicks();

		fpsCount++;
		if (fpsCount % 36 == 0)
			bool debug = true;

		// input
		// -----
		Move_Commands moveCommands = processInput(window);


		// Update
		// ------
		if (gameEntity->position.y < -50)
		{
			gameEntity->position = playerStart;
		}
		else
		{
			gameEntity->update(moveCommands, deltaTicks);
		}

		// Get blocks adjacent to player
		int playerLocX = gameEntity->position.x;
		int playerLocY = gameEntity->position.y;
		int playerLocZ = gameEntity->position.z;

		//for(int y = playerLocY)

		// Physics
		// -------

		// get a list of entities to test against
		// std::vector<GameEntity *> getCandidateBlocks(glm::vec3 originatingLocation, int blocksXZ, int blocksY);
		std::vector<GameEntity *> candidateBlocks = world.getCandidateBlocks(gameEntity->position, 3, 4);

		if (candidateBlocks.size() > 0)
		{
			//Collider collider(gameEntity, world.chunk()->entitiesVec());
			Collider collider(gameEntity, candidateBlocks);
			if (TEST_BREAK)
				collider.TEST_BREAK = true;
			collider.update();
		}


		// render
		// ------
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





		// View & Projection
		glm::mat4 view			= camera.GetViewMatrix();
		glm::mat4 projection	= glm::perspective(glm::radians(camera.Zoom), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		
		world.render(view, projection);


		// Draw a single object
		glm::mat4 model;
		model = glm::translate(model, gameEntity->position);
		gameEntity->entityModel->shader.setMat4("model", model);

		// Draw single
		gameEntity->entityModel->shader.setMat4("view", view);
		gameEntity->entityModel->shader.setMat4("projection", projection);
		gameEntity->entityModel->Draw(gameEntity->entityModel->shader);

		// glBindVertexArray(0); // no need to unbind it every time 


/*		// test the new Model and Mesh classes
		// render the loaded model
		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);
		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model2 = glm::scale(model2, glm::vec3(0.0f, 0.0f, 0.0f));	// it's a bit too big for our scene, so scale it down

		ourShader.setMat4("model", model2);
		ourModel.Draw(ourShader);
*/

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();

		if (fpsTimer >= 1.0f)
		{
			std::cout << "fps: " << fpsCount << "   ms: " << 1000.0 / float(fpsCount) << " : deltaTime: " << deltaTime << std::endl;
			std::cout << "\tLoc float : x " << gameEntity->position.x << "/ y " << gameEntity->position.y << "/ z " << gameEntity->position.z << std::endl;
			std::cout << "\tLoc int : x " << playerLocX << "/ y " << playerLocY << "/ z " << playerLocZ << std::endl;
			fpsTimer -= 1.0;
			fpsCount = 0;

			// Build additional world if needed
			std::tuple<int, int> playerPos = std::make_tuple((int)gameEntity->position.x, (int)gameEntity->position.z);
			world.updateChunks(playerPos);
		}

	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	////glDeleteVertexArrays(1, &VAO);
	////glDeleteBuffers(1, &VBO);
	////glDeleteBuffers(1, &EBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------

	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	screenWidth = width;
	screenHeight = height;
}

Move_Commands processInput(GLFWwindow *window)
{
	int testCommands = NULL;

	// A vector of enum Move_Commands listed on Motion.h
	Move_Commands moveCommands;
	float cameraSpeed = 2.5f * deltaTime;
	Camera_Movement cameraMovement = CAMERA_NO_MOVEMENT;
	glm::vec3 newPos = glm::vec3(gameEntity->position);

	// Close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	// move an object with arrow keys
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		moveCommands.MOVE_LEFT = true;
		//newPos.x -= MOVE_SPEED;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		moveCommands.MOVE_RIGHT = true;
		//newPos.x += MOVE_SPEED;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		moveCommands.MOVE_FORWARD = true;
		//newPos.z -= MOVE_SPEED;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		moveCommands.MOVE_BACKWARD = true;
		//newPos.z += MOVE_SPEED;
	}


	// Update movement position
	gameEntity->updatePosition(newPos);

	// Toggle mouse pointer
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		if (mouse_move)
		{
			// disable mouse_move
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			mouse_move = false;
			firstMouse = true;
		}
		else
		{	// enable mouse_move
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			mouse_move = true;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraMovement = FORWARD;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraMovement = BACKWARD;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraMovement = LEFT;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraMovement = RIGHT;
	camera.ProcessKeyboard(cameraMovement, deltaTime);

	return moveCommands;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if(firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset, true);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
