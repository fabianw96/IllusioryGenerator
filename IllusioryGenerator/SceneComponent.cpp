#include "SceneComponent.h"

SceneComponent::SceneComponent()
{
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
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
	return Position;
}

void SceneComponent::SetPosition(const glm::vec3& position)
{
	Position = position;
}
