#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Shader.h"

enum camera_movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

constexpr float YAW = -90.0f;
constexpr float PITCH = 0.0f;
constexpr float SPEED = 2.5f;
constexpr float SENSITIVITY = 0.1f;
constexpr float ZOOM = 90.0f;

class ViewPortCamera
{
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	//Vector constructor
	ViewPortCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

	//Scalar constructor
	ViewPortCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	//return view matrix from euler angles and look at matrix
	glm::mat4 GetViewMatrix() const;
	void ProcessKeyboardInput(camera_movement direction, float deltaTime);
	void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrain = true);
	void ProcessMouseScroll(float yOffset);
	void UpdateShaderMatrix(unsigned int screenWidth, unsigned int screenHeight);
	void SetShader(Shader* shaderProgram);
private:
	void updateCameraVectors();
	Shader* shader;
};
