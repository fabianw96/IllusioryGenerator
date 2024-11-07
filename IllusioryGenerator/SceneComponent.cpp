#include "SceneComponent.h"


SceneComponent::SceneComponent()
{
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
}

SceneComponent::~SceneComponent()
{
}

void SceneComponent::Update(float deltaTime)
{
}

void SceneComponent::Render()
{
}

glm::vec3 SceneComponent::GetPosition() const
{
	return m_position;
}

void SceneComponent::SetPosition(const glm::vec3& position)
{
	m_position = position;
}
