#pragma once
#include <array>
#include <vector>

#include "SceneComponent.h"
#include "Primitives.h"

class MeshComponent : public SceneComponent
{
public:
	void Render();
private:
	std::array<float, 180> verts = {};
};
