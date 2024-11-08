#ifndef SCENECOMPONENT_H
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
	virtual void SetPositionAndScale(const std::shared_ptr<ViewPortCamera>& viewPortCamera, glm::vec3 scale);

protected:
	glm::vec3 m_position;
	glm::vec3 m_scale;
};

#endif