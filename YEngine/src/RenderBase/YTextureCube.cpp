
#define GLEW_STATIC
#include "glew.h"
#include "YTextureCube.h"
#include "stb_image.h"

YTextureCube* YTextureCube::create(const std::string& positive_x, const std::string& negative_x, const std::string& positive_y, const std::string& negative_y, const std::string& positive_z, const std::string& negative_z)
{
	YTextureCube* _text = new(std::nothrow) YTextureCube;
	if (_text&&_text->init(positive_x,negative_x,positive_y,negative_y,positive_z,negative_z))
	{
		return _text;
	}
	delete _text;
	_text = nullptr;
	return nullptr;
}

YTextureCube::YTextureCube()
{

}

YTextureCube::~YTextureCube()
{

}

bool YTextureCube::init(const std::string& positive_x, const std::string& negative_x, const std::string& positive_y, const std::string& negative_y, const std::string& positive_z, const std::string& negative_z)
{
	m_vFilepath.push_back(positive_x);
	m_vFilepath.push_back(negative_x);
	m_vFilepath.push_back(positive_y);
	m_vFilepath.push_back(negative_y);
	m_vFilepath.push_back(positive_z);
	m_vFilepath.push_back(negative_z);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
	stbi_set_flip_vertically_on_load(false);
	int width, height, nrChannels;
	for (int i = 0;i<m_vFilepath.size();++i)
	{
		unsigned char *data = stbi_load(m_vFilepath[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			if (nrChannels==3)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else if(nrChannels == 4)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			
		}
		else
		{
			stbi_image_free(data);
			return false;
		}
		
		
	}
	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	return true;
}

