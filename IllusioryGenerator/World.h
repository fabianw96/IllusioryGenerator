#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <iostream>
#include "Shader.h"
#include "ViewPortCamera.h"
#include "ObjectTypes.h"
#include <chrono>
#include "Actor.h"

class Actor;

class World
{
public:
	World(const std::shared_ptr<ViewPortCamera>& viewPortCamera, const std::shared_ptr<Shader>& shader);
	~World();

	void AddActor(ObjectType actorType);
	void DeleteActor();
	void Update(float deltaTime);
private:
	std::vector<std::shared_ptr<Actor>> m_actors;
	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<ViewPortCamera> m_viewPortCamera;
};

#endif
