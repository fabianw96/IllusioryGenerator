#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "SceneComponent.h"

class Actor
{
public:
	Actor(const std::string& actorName, bool IsActive);
	virtual ~Actor();

	void AddComponent(SceneComponent* component);
	virtual void Update(float deltaTime);

protected:
	std::vector<SceneComponent*> Components;
	std::string m_ActorName;
	bool m_IsActive = true;
};
