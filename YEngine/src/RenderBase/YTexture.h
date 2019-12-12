#ifndef YTEXTURE_H_
#define YTEXTURE_H_
#include <string>
class YTexture
{
public:
	enum ImageType
	{
		IMAGE_RGB,
	    IMAGE_RGBA
	};
public:
	YTexture(const char* _path, ImageType _type=IMAGE_RGB);
	virtual ~YTexture();

public:
	static unsigned int CreateText(const char* _path);
	static unsigned int CreateText(const char* _path, ImageType _type);
protected:
	bool init();
protected:
	unsigned int m_texture;
	std::string  m_strPath;
	ImageType    m_type;
};


#endif
#pragma once
