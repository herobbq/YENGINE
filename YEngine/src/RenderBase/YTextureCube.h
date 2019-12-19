#ifndef YTEXTURECUBE_H_
#define YTEXTURECUBE_H_

#include "YTexture2D.h"
#include <vector>
class YTextureCube :public YTexture2D
{
public:
	static YTextureCube* create(const std::string& positive_x, const std::string& negative_x,
		const std::string& positive_y, const std::string& negative_y,
		const std::string& positive_z, const std::string& negative_z);
protected:
	YTextureCube();
	~YTextureCube();
protected:
	bool init(const std::string& positive_x, const std::string& negative_x,
		const std::string& positive_y, const std::string& negative_y,
		const std::string& positive_z, const std::string& negative_z);
protected:
	std::vector<std::string> m_vFilepath;
};
#endif