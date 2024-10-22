#include "World.h"

World::World()
{

}

World::~World()
{
}

void World::AddActor(Actor* actor)
{
	Actors.emplace_back(actor);
	std::cout << "New Actor: " << actor << " added to World!" << "\n";
}

void World::DeleteActor(Actor* actor)
{
	Actors.erase(std::ranges::find(Actors, actor));
	std::cout << "Actor: " << actor << " deleted from World!" << "\n";
}

void World::Update(float deltaTime)
{
	for(auto actor : Actors)
	{
		actor->Update(deltaTime);
	}
}
