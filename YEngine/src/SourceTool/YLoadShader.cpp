#include"YLoadShader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h> 
using namespace std;
YShader::YShader(const char* vertexPath, const char* fragmentPath, const char*geometryPath)
	:ID(-1)
{
	char ErrorLog[512];
	string  vertexCode;
	string  fragmentCode;
	string  geometryCode;        

	ifstream vShaderFile;
	ifstream fShaderFile;
	ifstream gShaderFile;
	//ensure ifstream objects can throw exceptions
	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	gShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		if (geometryPath!=nullptr)
		{
			gShaderFile.open(geometryPath);
			stringstream gShaderStream;
			gShaderStream << gShaderFile.rdbuf();
			gShaderFile.close();
			geometryCode = gShaderStream.str();
		}

	}
	catch (ifstream::failure  e)
	{
		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
		return;
	}
	
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* gShaderCode = nullptr;
	if (geometryPath!=nullptr)
	{
		gShaderCode = geometryCode.c_str();
	}
	unsigned int ivertex,ifragment;

	ivertex = glCreateShader(GL_VERTEX_SHADER);
	ifragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(ivertex, 1, &vShaderCode, NULL);
	glCompileShader(ivertex);
	GLint  bResult = GL_FALSE;
	glGetShaderiv(ivertex, GL_COMPILE_STATUS, &bResult);
	if(bResult==GL_FALSE)
	{
		glGetShaderInfoLog(ivertex, 512, NULL, ErrorLog);
		cout << "ERROR::Vertex Shader Compile failed\n" << "Log : " << ErrorLog << endl;
	}
	glShaderSource(ifragment, 1, &fShaderCode, NULL);
	glCompileShader(ifragment);
	glGetShaderiv(ifragment, GL_COMPILE_STATUS, &bResult);
	if (bResult==GL_FALSE)
	{
		glGetShaderInfoLog(ifragment, 512, NULL, ErrorLog);
		cout << "ERROR::Fragment Shader Compile failed\n" << "Log : " << ErrorLog << endl;
	}
	unsigned int igeometry;
	if (geometryPath!=nullptr)
	{
		igeometry =  glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(igeometry, 1, &gShaderCode, NULL);
		glCompileShader(igeometry);
		glGetShaderiv(igeometry, GL_COMPILE_STATUS, &bResult);
		if (bResult == GL_FALSE)
		{
			glGetShaderInfoLog(igeometry, 512, NULL, ErrorLog);
			cout << "ERROR::Geometry Shader Compile failed\n" << "Log : " << ErrorLog << endl;
		}
	}
	ID = glCreateProgram();
	glAttachShader(ID, ivertex);
	glAttachShader(ID, ifragment);
	if (geometryPath != nullptr)
	{
		glAttachShader(ID, igeometry);
	}
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &bResult);
	if (bResult==GL_FALSE)
	{
		glGetProgramInfoLog(ID, 512, NULL, ErrorLog);
		cout << "ERROR::Program Link failed\n" << "Log:" << ErrorLog << endl;
	}
	glDeleteShader(ivertex);
	glDeleteShader(ifragment);
	if (geometryPath != nullptr)
	{
		glDeleteShader(igeometry);
	}
}

YShader::~YShader()
{

}

void YShader::use()
{
	glUseProgram(ID);
}

void YShader::SetBool(const std::string& name, bool Value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()),(int)Value);
}

void YShader::SetInt(const std::string& name, int Value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), Value);
}

void YShader::SetFloat(const std::string& name, float Value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), Value);
}

void YShader::SetVec2(const std::string& name, glm::vec2& Value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1,&Value[0]);
}

void YShader::SetVec3(const std::string&name, glm::vec3&Value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &Value[0]);
}

void YShader::SetVec4(const std::string&name, glm::vec4&Value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &Value[0]);
}

void YShader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1,GL_FALSE, &mat[0][0]);
}

void YShader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void YShader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

