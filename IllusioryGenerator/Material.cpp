#include "Material.h"

Material::Material(float r, float g, float b, const std::string& texturePath, std::shared_ptr<Shader> shader)
	: red(r), green(g), blue(b), m_Shader(std::move(shader))
{
	texPath = texturePath;
	glGenTextures(1, &textureID);
	TextureLoader::loadTexture(texPath.c_str());
	m_Shader->use();
	m_Shader->setInt("texture1", 0);
}

Material::~Material()
= default;

void Material::ApplyMaterial()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}
