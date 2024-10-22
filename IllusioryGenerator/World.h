#pragma once
#include <vector>
#include "Actor.h"
#include <iostream>

class World
{
public:
	World();
	~World();

	void AddActor(Actor* actor);
	void DeleteActor(Actor* actor);
	void Update(float deltaTime);

private:
	std::vector<Actor*> Actors;

};
