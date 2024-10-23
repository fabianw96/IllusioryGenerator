#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "SceneComponent.h"

class Actor
{
public:
	Actor(const int& m_ActorID, bool IsActive);
	virtual ~Actor();

	void AddComponent(std::unique_ptr<SceneComponent> component);
	virtual void Update(float deltaTime);

protected:
	std::vector<std::unique_ptr<SceneComponent>> Components;
	int m_ActorID = 0;
	bool m_IsActive = true;
};
