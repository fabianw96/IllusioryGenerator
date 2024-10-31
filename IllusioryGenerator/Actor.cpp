#include "Actor.h"

Actor::Actor(const int& actorID, bool isActive, const std::shared_ptr<Shader>& shader) : m_shader(shader)
{
	m_ActorID = actorID;
	m_IsActive = isActive;
}

void Actor::Init()
{
	std::unique_ptr<MeshComponent> meshComponent = std::make_unique<MeshComponent>("./Assets/Models/backpack.obj", m_shader);
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
			meshComponent->Draw();
		}
	}
}
