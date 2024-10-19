#include "TextureLoader.h"

void TextureLoader::loadTexture(char const* file, unsigned int texture)
{
	int width;
	int height;
	int nrChannels;
	GLenum format = 0;


	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

	switch(nrChannels)
	{
	case 1: format = GL_RED;
		break;
	case 2: format = GL_RG;
		break;
	case 3: format = GL_RGB;
		break;
	case 4: format = GL_RGBA;
		break;
	default:
		std::cout << "Channel format of input not valid" << "\n";
		break;
	}

	if(data)
	{
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << "\n";
	}

	stbi_image_free(data);
}
