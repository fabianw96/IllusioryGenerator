﻿#ifndef SCENECOMPONENT_H
#define SCENECOMPONENT_H
#include <glm/glm.hpp>
#include <iostream>
#include "ViewPortCamera.h"


class SceneComponent
{
public:
	SceneComponent();
	virtual ~SceneComponent();

	virtual void Update(float deltaTime);
	virtual void Render();

	glm::vec3 GetPosition() const;
	void SetPosition(const glm::vec3& position);

protected:
	glm::vec3 m_position;
};

#endif