#ifndef YLOADSHADER_H_
#define YLOADSHADER_H_

#include <glm/glm.hpp>
#include <string>
class YShader
{
public:
	explicit YShader(const char* vertexPath, const char* fragmentPath,const char*geometryPath = nullptr);
	virtual ~YShader();
	void use();
	void SetBool(const std::string& name,bool Value)const;
	void SetInt(const std::string& name,int Value)const;
	void SetFloat(const std::string& name, float Value)const;
	void SetVec2(const std::string& name, glm::vec2& Value)const;
	void SetVec3(const std::string&name, glm::vec3&Value)const;
	void SetVec4(const std::string&name, glm::vec4&Value)const;
	void setMat2(const std::string &name, const glm::mat2 &mat) const;
	void setMat3(const std::string &name, const glm::mat3 &mat) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
private:
	unsigned int ID;

};











#endif // 
