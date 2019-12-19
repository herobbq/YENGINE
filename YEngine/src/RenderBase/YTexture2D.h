#ifndef YTEXTURE_H_
#define YTEXTURE_H_
#include <string>
class YTexture2D
{
public:
	enum ImageType
	{
		IMAGE_RGB,
	    IMAGE_RGBA
	};
public:
	
	static YTexture2D* create(const std::string& strFilePath);
	unsigned int GetName() { return m_texture; }
protected:
	bool init(const std::string& strFilePath);
	YTexture2D();
	virtual ~YTexture2D();
protected:
	unsigned int m_texture;
	std::string  m_strPath;
	ImageType    m_type;
	
};


#endif
#pragma once
