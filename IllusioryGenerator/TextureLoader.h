#pragma once

#include "stb_image.h"
#include <iostream>
#include <glad/glad.h>

class TextureLoader
{
public:
	static void loadTexture(char const* file, unsigned int texture);
};
