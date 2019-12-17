#define GLEW_STATIC
#include "glew.h"
#include "YTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

YTexture::YTexture(const char* _path, ImageType _type/*=IMAGE_RGB*/)
	:m_strPath(_path)
	,m_type(_type)
{

}

YTexture::~YTexture()
{

}

unsigned int YTexture::CreateText(const char* _path)
{
	return CreateText(_path, IMAGE_RGB);
}

unsigned int YTexture::CreateText(const char* _path, ImageType _type)
{

	YTexture _text(_path,_type);
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
		if (m_type==IMAGE_RGB)
		{
			glTexStorage2D(GL_TEXTURE_2D, 1 , GL_RGB8, width, height);
			glTexSubImage2D(GL_TEXTURE_2D, 0,0,0,  width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
		//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}else if (m_type == IMAGE_RGBA)
		{
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

