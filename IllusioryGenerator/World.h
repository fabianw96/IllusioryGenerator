#pragma once
#include <vector>
#include "Actor.h"

class World
{
public:
	World();
	~World();

	void AddActor(Actor* actor);
	void Update(float deltaTime);
	void Render();

private:
	std::vector<Actor*> Actors;

};
