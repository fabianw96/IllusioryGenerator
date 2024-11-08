#include "Actor.h"


Actor::Actor(const int& actorID, bool isActive, const std::shared_ptr<Shader>& shader) : m_shader(shader)
{
	m_ActorID = actorID;
	m_IsActive = isActive;
}

void Actor::Init(const std::shared_ptr<ViewPortCamera>& viewPortCamera, ObjectType actorType)
{
	std::unique_ptr<MeshComponent> meshComponent;
	std::unique_ptr<LightComponent> lightComponent;


	if(actorType == OT_CUBE)
	{
		meshComponent = std::make_unique<MeshComponent>("./Assets/Models/Cube/Cube.obj", m_shader);
		meshComponent->SetPositionAndScale(viewPortCamera, glm::vec3(1.0f, 1.0f, 1.0f));
		this->AddComponent(std::move(meshComponent));
	}
	else if(actorType == OT_BACKPACK)
	{
		meshComponent = std::make_unique<MeshComponent>("./Assets/Models/Backpack/Backpack.obj", m_shader);
		meshComponent->SetPositionAndScale(viewPortCamera, glm::vec3(1.0f, 1.0f, 1.0f));
		this->AddComponent(std::move(meshComponent));
	}
	else if(actorType == OT_LIGHT)
	{
		//Create Actor with a LightComponent. This needs no model.
		lightComponent = std::make_unique<LightComponent>(m_shader);
		meshComponent = std::make_unique<MeshComponent>("./Assets/Models/Cube/Cube.obj", m_shader);
		meshComponent->SetPositionAndScale(viewPortCamera, glm::vec3(0.2f, 0.2f, 0.2f));
		this->AddComponent(std::move(meshComponent));
		lightComponent->SetPositionAndScale(viewPortCamera, glm::vec3(1.0f, 1.0f, 1.0f));
		this->AddComponent(std::move(lightComponent));
	}
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
		if(auto lightComponent = dynamic_cast<LightComponent*>(component.get()))
		{
			m_numLights++;

			m_shader->use();
			m_shader->setInt("numLights", m_numLights);
		}
	}
}
