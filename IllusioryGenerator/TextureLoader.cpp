#include "TextureLoader.h"

void TextureLoader::loadTexture(char const* file)
{
	int width;
	int height;
	int nrChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

	if(data)
	{
		GLenum format = 0;
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

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Failed to load texture" << "\n";
	}

	stbi_image_free(data);

}
