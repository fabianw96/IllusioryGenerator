#pragma once
#include <vector>
#include "Actor.h"
#include <iostream>

class World
{
public:
	World();
	~World();

	void AddActor(std::unique_ptr<Actor> actor);
	void DeleteActor(std::unique_ptr<Actor> actor);
	void Update(float deltaTime);
private:
	std::vector<std::unique_ptr<Actor>> Actors;

};
