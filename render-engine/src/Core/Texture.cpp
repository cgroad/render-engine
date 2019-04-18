#define  STB_IMAGE_IMPLEMENTATION
#include "Core/Texture.h"
#include "std_image.h"
#include "glad/glad.h"
Texture::Texture(const char* path, int textureUnit, int colorMode)
{
	this->textureUnit = textureUnit;
	glGenTextures(1, &textureId);
	glActiveTexture(this->textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureId);
	//设置环绕方式和过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//加载并生成纹理
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR: failed to load texture: " + string(path) << std::endl;
	}
	stbi_image_free(data);
}

void Texture::use()
{
	glActiveTexture(this->textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureId);
}