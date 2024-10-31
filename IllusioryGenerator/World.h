#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <iostream>

#include "Shader.h"

class Actor;

class World
{
public:
	World(const std::shared_ptr<Shader>& shader);
	~World();

	void AddActor();
	void DeleteActor(std::shared_ptr<Actor> actor);
	void Update(float deltaTime);
private:
	std::vector<std::shared_ptr<Actor>> Actors;
	std::shared_ptr<Shader> m_shader;
};

#endif
