#pragma once
#include <vector>
#include "SceneComponent.h"

class Actor
{
public:
	Actor();
	virtual ~Actor();

	void AddComponent(SceneComponent* component);
	virtual void Update(float deltaTime);
	virtual void Render();

protected:
	std::vector<SceneComponent*> Components;
	
};
