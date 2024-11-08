#include "MeshComponent.h"


void MeshComponent::Draw()
{
	for(unsigned int i = 0; i < m_meshes.size(); ++i)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, m_position);
		model = glm::scale(model, m_scale);

		m_Shader->use();
		m_Shader->setMat4("model", model);

		m_meshes[i].RenderMesh();
	}
}

void MeshComponent::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << "\n";
		return;
	}
	std::cout << "Loading model..." << "\n";

	m_directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void MeshComponent::processNode(aiNode* node, const aiScene* scene)
{
	for(unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, scene));
	}

	for(unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}
MeshLoader MeshComponent::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for(unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector;

		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		if(mesh->HasNormals())
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}

		if(mesh->mTextureCoords[0])
		{
			glm::vec2 vec;

			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;

			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.Tangent = vector;

			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.Bitangent = vector;
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	for(int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for(unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

	std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	return MeshLoader(vertices, indices, textures, m_Shader);
}

std::vector<Texture> MeshComponent::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// std::cout << mat->GetTextureCount(type) << " : " << str.C_Str();
		bool skip = false;
		for(int j = 0; j < m_textures_loaded.size(); j++)
		{
			if(std::strcmp(m_textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(m_textures_loaded[j]);
				skip = true;
				break;
			}
		}

		if(!skip)
		{
			Texture texture;
			texture.id = TextureLoader::loadTexture(str.C_Str(), m_directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			m_textures_loaded.push_back(texture);
		}
	}

	return textures;
}

void MeshComponent::SetPositionAndScale(const std::shared_ptr<ViewPortCamera>& viewPortCamera, glm::vec3 scale)
{
	glm::vec3 spawnPosition = viewPortCamera->GetPosition() + viewPortCamera->GetFront() * 5.0f;
	m_scale = scale;
	m_position = spawnPosition;
}


