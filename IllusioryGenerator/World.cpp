#include "World.h"


World::World(const std::shared_ptr<ViewPortCamera>& viewPortCamera, const std::shared_ptr<Shader>& shader) : m_shader(shader), m_viewPortCamera(viewPortCamera)
{
}

World::~World()
{
}

void World::AddActor(ObjectType actorType)
{
	unsigned long time_since_epoch = std::chrono::system_clock::now().time_since_epoch() / std::chrono::seconds(1);
	std::shared_ptr<Actor> newActor = std::make_shared<Actor>(time_since_epoch, true, m_shader);
	m_actors.emplace_back(newActor);
	std::cout << "New Actor: " << newActor << " added to World!" << "\n";
	newActor->Init(m_viewPortCamera, actorType);
}

void World::DeleteActor()
{
	std::cout << "Actor: " << m_actors.cend()->get() << " deleted from World!" << "\n";
	m_actors.erase(m_actors.cend());
}

void World::Update(float deltaTime)
{
	for(auto& actor : m_actors)
	{
		actor->Update(deltaTime);
	}
}
