#pragma once
#include <glm/glm.hpp>

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
	glm::vec3 Position;
};
