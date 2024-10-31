#ifndef ACTOR_H
#define ACTOR_H
#include <iostream>
#include <string>
#include <vector>
#include "SceneComponent.h"
#include "MeshComponent.h"
#include "World.h"

class Actor
{
public:
	Actor(const int& m_ActorID, bool IsActive, const std::shared_ptr<Shader>& shader);
	void	Init();
	virtual ~Actor();

	void AddComponent(std::unique_ptr<SceneComponent> component);
	virtual void Update(float deltaTime);

protected:
	std::vector<std::unique_ptr<SceneComponent>> Components;
	std::shared_ptr<Shader> m_shader;
	int m_ActorID = 0;
	bool m_IsActive = true;
};

#endif
