#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include <array>
#include "Material.h"
#include "MeshLoader.h"
#include "SceneComponent.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class MeshComponent : public SceneComponent
{
public:
	MeshComponent(const char* path, std::shared_ptr<Shader> shader) : m_Shader(shader)
	{
		loadModel(path);
	}

	std::vector<Texture> textures_loaded;

	void Draw();
private:
	std::vector<MeshLoader> meshes;
	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	MeshLoader processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	std::shared_ptr<Shader> m_Shader;
};

#endif