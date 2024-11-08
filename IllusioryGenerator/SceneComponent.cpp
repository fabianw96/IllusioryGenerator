#include "SceneComponent.h"


SceneComponent::SceneComponent()
{
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_scale = glm::vec3(0.0f, 0.0f, 0.0f);
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

void SceneComponent::SetPositionAndScale(const std::shared_ptr<ViewPortCamera>& viewPortCamera, glm::vec3 scale)
{

}
