#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>

#include "Actor.h"
#include "Material.h"
#include "MeshComponent.h"
#include "ViewPortCamera.h"
#include "Shader.h"
#include "stb_image.h"
#include "TextureLoader.h"
#include "World.h"

//Settings
constexpr unsigned int SCREEN_WIDTH = 800;
constexpr unsigned int SCREEN_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
unsigned int loadCubemap(std::vector<std::string> faces);

//timings
float deltaTime = 0;
float lastFrameTime = 0;

//camera
ViewPortCamera viewPortCam(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouseInput = true;

//input
bool isSpawnPressed = false;
bool isDeletePressed = true;

std::shared_ptr<Shader> shaderProgram;
std::shared_ptr<World> 	world;

int main(int argc, char* argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Illusiory Generator", nullptr, nullptr);

	if(window == nullptr)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	GLADloadproc gladGetProcAddress = (GLADloadproc)glfwGetProcAddress;

	if(gladGetProcAddress == nullptr)
	{
		std::cout << "Failed to init GLAD\n";
		return -1;
	}

	if (!gladLoadGLLoader(gladGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << '\n';
		return -1;
	}

	shaderProgram = std::make_shared<Shader>("vertShader.glsl", "fragShader.glsl");
	world = std::make_shared<World>(shaderProgram);
	viewPortCam.SetShader(shaderProgram);

	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//cubemap/skybox
	//_______________________________________________________

	Shader skyboxShader("./skyboxVertShader.glsl", "./skyboxFragShader.glsl");
	float skyboxVertices[] = {
		// positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	std::vector<std::string> faces
	{
		"./skybox/right.jpg",
		"./skybox/left.jpg",
		"./skybox/top.jpg",
		"./skybox/bottom.jpg",
		"./skybox/front.jpg",
		"./skybox/back.jpg"
	};

	unsigned int cubemapTexture = loadCubemap(faces);

	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);
	//_______________________________________________________

	//rendering loop
	//_______________________________________________________
	while(!glfwWindowShouldClose(window))
	{
		//frame time logic
		float currentframe = static_cast<float>(glfwGetTime());
		deltaTime = currentframe - lastFrameTime;
		lastFrameTime = currentframe;

		//input processing
		processInput(window);

		//rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		viewPortCam.UpdateShaderMatrix(SCREEN_WIDTH, SCREEN_HEIGHT);
		world->Update(deltaTime);

		glDepthFunc(GL_LEQUAL);

		// skyboxShader.use();
		// glm::mat4 view = glm::mat4(glm::mat3(viewPortCam.GetViewMatrix()));
		// skyboxShader.setMat4("view", view);
		// skyboxShader.setMat4("projection", viewPortCam.GetProjectionmatrix(SCREEN_WIDTH, SCREEN_HEIGHT));

		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);

		//check for events, call events, swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);

	}

	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0,0,width,height);
}

void processInput(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window,true);

	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		viewPortCam.ProcessKeyboardInput(FORWARD, deltaTime);

	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		viewPortCam.ProcessKeyboardInput(BACKWARD, deltaTime);

	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		viewPortCam.ProcessKeyboardInput(LEFT, deltaTime);

	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		viewPortCam.ProcessKeyboardInput(RIGHT, deltaTime);

	if(glfwGetKey(window, GLFW_MOUSE_BUTTON_RIGHT == GLFW_PRESS))
	{
		glfwSetCursorPosCallback(window, mouse_callback);
	}

	if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	{
		if(!isSpawnPressed)
		{
			world->AddActor();
			isSpawnPressed = true;
		}
	}
	else
	{
		isSpawnPressed = false;
	}

	//TODO: Currently bugged, should delete actor by last created
	// if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	// {
	// 	if(!isDeletePressed)
	// 	{
	// 		world->DeleteActor(newActor);
	// 		isDeletePressed = true;
	// 	}
	// }
	// else
	// {
	// 	isDeletePressed = false;
	// }
}

void mouse_callback(GLFWwindow* window, double xPosIn, double yPosIn)
{
	float xPos = static_cast<float>(xPosIn);
	float yPos = static_cast<float>(yPosIn);

	if(firstMouseInput)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouseInput = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	viewPortCam.ProcessMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	viewPortCam.ProcessMouseScroll(static_cast<float>(yOffset));
}

unsigned int loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << "\n";
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
