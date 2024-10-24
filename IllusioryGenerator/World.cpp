#include "World.h"

#include <chrono>

#include "Actor.h"

World::World(const std::shared_ptr<Shader>& shader) : m_shader(shader)
{
}

World::~World()
{
}

void World::AddActor()
{
	unsigned long time_since_epoch = std::chrono::system_clock::now().time_since_epoch() / std::chrono::seconds(1);
	std::shared_ptr<Actor> newActor = std::make_shared<Actor>(time_since_epoch, true, m_shader);
	Actors.emplace_back(newActor);
	std::cout << "New Actor: " << newActor << " added to World!" << "\n";
	newActor->Init();
}

void World::DeleteActor(std::shared_ptr<Actor> actor)
{
	std::cout << "Actor: " << actor << " deleted from World!" << "\n";
	Actors.erase(std::ranges::find(Actors, actor));
}

void World::Update(float deltaTime)
{
	for(auto& actor : Actors)
	{
		actor->Update(deltaTime);
	}
}
