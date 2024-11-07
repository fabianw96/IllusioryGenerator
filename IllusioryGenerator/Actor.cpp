#include "Actor.h"

Actor::Actor(const int& actorID, bool isActive, const std::shared_ptr<Shader>& shader) : m_shader(shader)
{
	m_ActorID = actorID;
	m_IsActive = isActive;
}

void Actor::Init(const std::shared_ptr<ViewPortCamera>& viewPortCamera, ObjectType actorType)
{
	std::unique_ptr<MeshComponent> meshComponent;

	if(actorType == OT_CUBE)
	{
		meshComponent = std::make_unique<MeshComponent>("./Assets/Models/Cube/Cube.obj", m_shader);
	}
	else if(actorType == OT_BACKPACK)
	{
		meshComponent = std::make_unique<MeshComponent>("./Assets/Models/Backpack/Backpack.obj", m_shader);
	}

	glm::vec3 spawnPosition = viewPortCamera->GetPosition() + viewPortCamera->GetFront() * 5.0f;

	meshComponent->SetPosition(spawnPosition);
	this->AddComponent(std::move(meshComponent));
}

Actor::~Actor()
{
}

void Actor::AddComponent(std::unique_ptr<SceneComponent> component)
{
	std::cout << "Component: " << component.get() << " added to Actor!" << "\n";
	m_components.emplace_back(std::move(component));
}

void Actor::Update(float deltaTime)
{
	for(auto& component : m_components)
	{
		component->Update(deltaTime);

		if(auto meshComponent = dynamic_cast<MeshComponent*>(component.get()))
		{
			meshComponent->Draw();
		}
	}
}
