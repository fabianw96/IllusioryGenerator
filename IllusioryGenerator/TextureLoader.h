#ifndef TEXTURE_LOADER
#define TEXTURE_LOADER

#include "stb_image.h"
#include <iostream>
#include <glad/glad.h>

class TextureLoader
{
public:
	static unsigned int loadTexture(char const* path, const std::string &directory);
};

#endif
