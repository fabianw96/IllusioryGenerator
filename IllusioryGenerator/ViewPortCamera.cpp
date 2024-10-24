#include "ViewPortCamera.h"

#include <iostream>
#include <glm/ext/matrix_clip_space.hpp>

ViewPortCamera::ViewPortCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;

	updateCameraVectors();
}

ViewPortCamera::ViewPortCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;

	updateCameraVectors();
}

glm::mat4 ViewPortCamera::GetViewMatrix() const
{
	return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 ViewPortCamera::GetProjectionmatrix(unsigned int screenWidth, unsigned int screenHeight) const
{
	return glm::perspective(glm::radians(Zoom), float(screenWidth) / float(screenHeight), 0.1f, 100.0f);
}

void ViewPortCamera::ProcessKeyboardInput(camera_movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;

	if(direction == FORWARD)
		Position += Front * velocity;
	if(direction == BACKWARD)
		Position -= Front * velocity;
	if(direction == LEFT)
		Position -= Right * velocity;
	if(direction == RIGHT)
		Position += Right * velocity;
}

void ViewPortCamera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrain)
{
	yOffset *= MouseSensitivity;
	xOffset *= MouseSensitivity;

	Yaw += xOffset;
	Pitch += yOffset;

	if(constrain)
	{
		if(Pitch > 89.0f)
			Pitch = 89.0f;
		if(Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVectors();
}

void ViewPortCamera::ProcessMouseScroll(float yOffset)
{
	Zoom -= yOffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 90.0f)
		Zoom = 90.0f;
}

void ViewPortCamera::UpdateShaderMatrix(unsigned int screenWidth, unsigned int screenHeight)
{
	shader->use();
	shader->setMat4("view", GetViewMatrix());
	shader->setMat4("projection", GetProjectionmatrix(screenWidth, screenHeight));
}

void ViewPortCamera::SetShader(const std::shared_ptr<Shader>& shaderProgram)
{
	shader = shaderProgram;
}


void ViewPortCamera::updateCameraVectors()
{
	glm::vec3 cameraFront;
	cameraFront.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	cameraFront.y = sin(glm::radians(Pitch));
	cameraFront.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(cameraFront);

	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}
