#pragma once
#include <memory>

#include "SceneComponent.h"
#include "Shader.h"

class LightComponent : public SceneComponent
{
public:
	LightComponent(const std::shared_ptr<Shader>& shader);
	void Update(float deltaTime) override;
	void SetPositionAndScale(const std::shared_ptr<ViewPortCamera>& viewPortCamera, glm::vec3 scale) override;
private:
	std::shared_ptr<Shader> m_shader;
	int m_lightIndex;
	static int s_nextLightIndex;
};

