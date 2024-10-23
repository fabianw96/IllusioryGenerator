#include "World.h"

World::World()
{
}

World::~World()
{
}

void World::AddActor(std::unique_ptr<Actor> actor)
{
	std::cout << "New Actor: " << actor << " added to World!" << "\n";
	Actors.emplace_back(std::move(actor));
}

void World::DeleteActor(std::unique_ptr<Actor> actor)
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
