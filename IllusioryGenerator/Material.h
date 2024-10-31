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
	float red, green, blue;
	unsigned int textureID;
	std::string texPath;
	std::shared_ptr<Shader> m_Shader;
};

#endif
