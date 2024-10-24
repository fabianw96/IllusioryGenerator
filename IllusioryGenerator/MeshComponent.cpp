﻿#include "MeshComponent.h"
#include <iostream>
#include <memory>
#include <glad/glad.h>
#include <glm/ext/matrix_transform.hpp>

MeshComponent::MeshComponent(const std::shared_ptr<Shader>& shader) : m_Shader(shader)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

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
	std::unique_ptr<Material> meshMaterial = std::make_unique<Material>(1.0f, 0.0f, 0.0f, "./awesomeface.png", m_Shader);

	m_Shader->use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	m_Shader->setMat4("model", model);

	glBindVertexArray(VAO);
	meshMaterial->ApplyMaterial();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	// std::cout << "Mesh Rendered!" << "\n";
}
