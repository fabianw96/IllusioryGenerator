#include "Actor.h"


Actor::Actor(const std::string& actorName, [[maybe_unused]] bool isActive)
{
	m_ActorName = actorName;
	m_IsActive = isActive;
}

Actor::~Actor()
{
}

void Actor::AddComponent(SceneComponent* component)
{
	Components.emplace_back(component);
	std::cout << "Component: " << component << " added to Actor!" << "\n";
}

void Actor::Update(float deltaTime)
{
	for(auto component : Components)
	{
		component->Update(deltaTime);
	}
}
