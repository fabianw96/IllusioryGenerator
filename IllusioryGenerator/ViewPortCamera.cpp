#include "ViewPortCamera.h"


ViewPortCamera::ViewPortCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : m_front(glm::vec3(0.0f, 0.0f, -1.0)), m_movementSpeed(SPEED), m_mouseSensitivity(SENSITIVITY), m_zoom(ZOOM)
{
	m_position = position;
	m_worldUp = up;
	m_yaw = yaw;
	m_pitch = pitch;

	UpdateCameraVectors();
}

ViewPortCamera::ViewPortCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : m_front(glm::vec3(0.0f, 0.0f, -1.0)), m_movementSpeed(SPEED), m_mouseSensitivity(SENSITIVITY), m_zoom(ZOOM)
{
	m_position = glm::vec3(posX, posY, posZ);
	m_worldUp = glm::vec3(upX, upY, upZ);
	m_yaw = yaw;
	m_pitch = pitch;

	UpdateCameraVectors();
}

glm::mat4 ViewPortCamera::GetViewMatrix() const
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 ViewPortCamera::GetProjectionmatrix(unsigned int screenWidth, unsigned int screenHeight) const
{
	return glm::perspective(glm::radians(m_zoom), float(screenWidth) / float(screenHeight), 0.1f, 100.0f);
}

glm::mat4 ViewPortCamera::SetModelMatrix() const
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, m_spawnPosition);
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

	return model;
}

glm::vec3 ViewPortCamera::GetPosition() const
{
	return m_position;
}

glm::vec3 ViewPortCamera::GetFront() const
{
	return m_front;
}

void ViewPortCamera::ProcessKeyboardInput(camera_movement direction, float deltaTime)
{
	float velocity = m_movementSpeed * deltaTime;

	if(direction == FORWARD)
		m_position += m_front * velocity;
	if(direction == BACKWARD)
		m_position -= m_front * velocity;
	if(direction == LEFT)
		m_position -= m_right * velocity;
	if(direction == RIGHT)
		m_position += m_right * velocity;
}

void ViewPortCamera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrain)
{
	yOffset *= m_mouseSensitivity;
	xOffset *= m_mouseSensitivity;

	m_yaw += xOffset;
	m_pitch += yOffset;

	if(constrain)
	{
		if(m_pitch > 89.0f)
			m_pitch = 89.0f;
		if(m_pitch < -89.0f)
			m_pitch = -89.0f;
	}

	UpdateCameraVectors();
}

void ViewPortCamera::ProcessMouseScroll(float yOffset)
{
	m_zoom -= yOffset;
	if (m_zoom < 1.0f)
		m_zoom = 1.0f;
	if (m_zoom > 90.0f)
		m_zoom = 90.0f;
}

void ViewPortCamera::UpdateShaderMatrix(unsigned int screenWidth, unsigned int screenHeight)
{
	m_shader->use();
	m_shader->setMat4("view", GetViewMatrix());
	m_shader->setMat4("projection", GetProjectionmatrix(screenWidth, screenHeight));
	m_shader->setMat4("model", SetModelMatrix());
	m_shader->setVec3("viewPos", GetPosition());
}



void ViewPortCamera::SetShader(const std::shared_ptr<Shader>& shaderProgram)
{
	m_shader = shaderProgram;
}


void ViewPortCamera::UpdateCameraVectors()
{
	glm::vec3 cameraFront;
	cameraFront.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	cameraFront.y = sin(glm::radians(m_pitch));
	cameraFront.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(cameraFront);
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}
