#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& fileName)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	int w, h, comp;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(fileName.c_str(), &w, &h, &comp, 4);
	if (!data)
	{
		printf("%s -> %s\n", fileName.c_str(), stbi_failure_reason());
		exit(0);
	}
	printf("Loaded texture %s\n", fileName.c_str());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	stbi_image_free(data);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
}
