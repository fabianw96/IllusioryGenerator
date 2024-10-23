#pragma once
#include <array>
#include <vector>

#include "Material.h"
#include "SceneComponent.h"
#include "Primitives.h"

class MeshComponent : public SceneComponent
{
public:
	MeshComponent();
	~MeshComponent();
	void RenderMesh();
private:
	// float verts[];
	unsigned int VBO, VAO;
	std::vector<float> verts;
	//create a new Shader for each mesh
	std::shared_ptr<Shader> shader = std::make_shared<Shader>("./vertShader.glsl", "./fragShader.glsl");
};
