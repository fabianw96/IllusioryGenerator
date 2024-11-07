#ifndef MATERIAL_H
#define MATERIAL_H
#include "Shader.h"
#include "TextureLoader.h"

class Material
{
public:
	Material(float r, float g, float b, const std::string& texturePath, std::shared_ptr<Shader> shader);
	~Material();
	void ApplyMaterial();

private:
	float m_red, m_green, m_blue;
	unsigned int m_textureID;
	std::string m_texPath;
	std::shared_ptr<Shader> m_Shader;
};

#endif
