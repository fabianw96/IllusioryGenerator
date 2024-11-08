#include "LightComponent.h"

LightComponent::LightComponent(const std::shared_ptr<Shader>& shader) : m_shader(shader)
{
	m_lightIndex = s_nextLightIndex++;
	std::cout << m_lightIndex << "\n";
}

void LightComponent::Update(float deltaTime)
{
	glm::vec3 lightPos = m_position;
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 lightSpecular =glm::vec3(1.0f, 1.0f, 1.0f);

	m_shader->use();
	m_shader->setVec3("lights[" + std::to_string(m_lightIndex) + "].position", lightPos);
	m_shader->setVec3("lights[" + std::to_string(m_lightIndex) + "].diffuse", lightColor * 0.5f);
	m_shader->setVec3("lights[" + std::to_string(m_lightIndex) + "].ambient", lightColor * 0.2f);
	m_shader->setVec3("lights[" + std::to_string(m_lightIndex) + "].specular", lightSpecular);

}

void LightComponent::SetPositionAndScale(const std::shared_ptr<ViewPortCamera>& viewPortCamera, glm::vec3 scale)
{
	glm::vec3 spawnPosition = viewPortCamera->GetPosition() + viewPortCamera->GetFront() * 5.0f;
	m_scale = scale;
	m_position = spawnPosition;
}

int LightComponent::s_nextLightIndex = 0;

