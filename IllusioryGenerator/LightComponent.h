#pragma once
#include <memory>

#include "Shader.h"

class LightComponent
{
public:
private:
	std::shared_ptr<Shader> m_shader;
};
