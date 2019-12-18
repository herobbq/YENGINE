#define GLEW_STATIC
#include "glew.h"
#include "YTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

YTexture::YTexture(const char* _path)
	:m_strPath(_path)
{

}

YTexture::~YTexture()
{

}

unsigned int YTexture::CreateText(const char* _path)
{
	YTexture _text(_path);
	if (_text.init())
	{
		return _text.m_texture;
	}
	return -1;
}


bool YTexture::init()
{
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(m_strPath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		if (nrChannels==3)
		{
			glTexStorage2D(GL_TEXTURE_2D, 1 , GL_RGB8, width, height);
			glTexSubImage2D(GL_TEXTURE_2D, 0,0,0,  width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}else if (nrChannels == 4)
		{
		//	unsigned int buf;
			//glCreateBuffers(1, &buf);
			//glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buf);
			//glNamedBufferStorage(buf, sizeof(data), data, 0);
			glTextureStorage2D(m_texture, 2, GL_RGBA32F, width, height);
			
			glTextureSubImage2D(m_texture, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		return false;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_image_free(data);
	return true;
}

