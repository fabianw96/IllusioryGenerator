#include "MeshComponent.h"

#include <iostream>
#include <memory>

void MeshComponent::Render()
{
	//TODO: Render loop for chosen mesh.
	std::unique_ptr<Box> boxPrimitive = std::make_unique<Box>();
	verts = boxPrimitive->GetVertices();

	std::cout << verts[1];
}
