#include "MeshComponent.h"
#include <iostream>
#include <memory>
#include <glad/glad.h>

MeshComponent::MeshComponent()
{
	std::unique_ptr<Box> boxPrimitive = std::make_unique<Box>();
	verts = boxPrimitive->verts;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), static_cast<void*>(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	MeshComponent::RenderMesh();
}


MeshComponent::~MeshComponent()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void MeshComponent::RenderMesh()
{
	//TODO: Render loop for chosen mesh.
	std::unique_ptr<Material> meshMaterial = std::make_unique<Material>(1.0f, 0.0f, 0.0f, "./awesomeface.png", shader);

	glBindVertexArray(VAO);
	shader->use();
	glActiveTexture(GL_TEXTURE0);
	meshMaterial->ApplyMaterial();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	std::cout << "Mesh Rendered!" << "\n";
}
