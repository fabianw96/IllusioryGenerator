﻿#ifndef VIEWPORT_CAMERA_H
#define VIEWPORT_CAMERA_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Shader.h"
#include <iostream>
#include <glm/ext/matrix_clip_space.hpp>

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
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	float m_yaw;
	float m_pitch;

	float m_movementSpeed;
	float m_mouseSensitivity;
	float m_zoom;

	glm::vec3 m_spawnPosition;

	//Vector constructor
	ViewPortCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

	//Scalar constructor
	ViewPortCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	//return view matrix from euler angles and look at matrix
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionmatrix(unsigned int screenWidth, unsigned int screenHeight) const;
	glm::mat4 SetModelMatrix() const;
	glm::vec3 GetPosition() const;
	glm::vec3 GetFront() const;
	void      ProcessKeyboardInput(camera_movement direction, float deltaTime);
	void      ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrain = true);
	void      ProcessMouseScroll(float yOffset);
	void      UpdateShaderMatrix(unsigned int screenWidth, unsigned int screenHeight);
	void      SetShader(const std::shared_ptr<Shader>& shaderProgram);
private:
	void UpdateCameraVectors();
	std::shared_ptr<Shader> m_shader;
};


#endif
