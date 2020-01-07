#include "hfileinclude.h"

#include "YTexture2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


YTexture2D::YTexture2D()
{

}

YTexture2D::~YTexture2D()
{

}

YTexture2D* YTexture2D::create(const std::string& strFilePath)
{
	YTexture2D* _text = new (std::nothrow)YTexture2D;
	if (_text->init(strFilePath))
	{
		return _text;
	}
	delete _text;
	_text = nullptr;
	return NULL;
}




bool YTexture2D::init(const std::string& strFilePath)
{
	m_strPath = strFilePath;
	int width, height, nrChannels;
	//stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(m_strPath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;
		if (nrChannels==3)
		{
           #ifdef TexImage2D
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
           #else
			glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, width, height);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
           #endif
			
			//
			
		}else if (nrChannels == 4)
		{
          #ifdef TEXTIMAGE2D
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
         #elseif COMPRESSED
           glTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		   GLint compFlag;
		   glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED, &compFlag);
		   assert(compFlag != 0)
        #else
			glTextureStorage2D(m_texture, 2, GL_RGBA32F, width, height);
			glTextureSubImage2D(m_texture, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
        #endif
		
		}
		
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_image_free(data);
		return true;
	}
	else
	{
		stbi_image_free(data);
		return false;
	}
	

	
	return true;
}





