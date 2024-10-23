#include "Actor.h"

#include "MeshComponent.h"


Actor::Actor(const int& actorID, [[maybe_unused]] bool isActive)
{
	m_ActorID = actorID;
	m_IsActive = isActive;
	std::unique_ptr<MeshComponent> meshComponent = std::make_unique<MeshComponent>();
	this->AddComponent(std::move(meshComponent));
}

Actor::~Actor()
{
}

void Actor::AddComponent(std::unique_ptr<SceneComponent> component)
{
	std::cout << "Component: " << component.get() << " added to Actor!" << "\n";
	Components.emplace_back(std::move(component));
}

void Actor::Update(float deltaTime)
{
	for(auto& component : Components)
	{
		component->Update(deltaTime);
		if(auto meshComponent = dynamic_cast<MeshComponent*>(component.get()))
		{
			meshComponent->RenderMesh();
		}
	}
}
