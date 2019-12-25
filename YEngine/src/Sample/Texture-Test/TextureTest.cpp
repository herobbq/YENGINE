#include "TextureTest.h"
#define GLEW_STATIC
#include "glew.h"
#include <glfw3.h>
#include "YRenderer.h"
#include "YLoadShader.h"
#include "GLProgram.h"
#include "YTexture2D.h"
TextureTest::TextureTest()
	:m_shader(nullptr)
	, m_Texture1(nullptr)
	, m_Texture2(nullptr)
{

}

TextureTest::~TextureTest()
{
	delete m_shader;
}
TextureTest* TextureTest::create()
{
	TextureTest* res = new (std::nothrow)TextureTest;
	if (res&&res->init())
	{
		return res;
	}
	delete res;
	res = nullptr;
	return nullptr;
}

void TextureTest::draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags)
{
	glm::mat4 value = transform;
	m_customCommand.init(1);
	m_customCommand.func = std::bind(&TextureTest::onDraw, this, &transform, flags);
	m_customCommand.setTransparent(false);
	m_customCommand.set3D(true);
	renderer->addCommand(&m_customCommand);
}

bool TextureTest::init()
{
	m_shader = new YShader("./src/Shader/Texture.vert", "./src/Shader/Texture.frag");
	initBuffers();
	return true;
}

void TextureTest::initBuffers()
{
	float vertices[] = {
		// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	glGenVertexArrays(1, &m_VAO);
	
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	m_shader->use();

	m_positionAttributeLocation = glGetAttribLocation(m_shader->GetProgram(), GLProgram::ATTRIBUTE_NAME_POSITION);
	m_ColorAttributeLocation = glGetAttribLocation(m_shader->GetProgram(), GLProgram::ATTRIBUTE_NAME_COLOR);
	m_TextureAttributeLocation = glGetAttribLocation(m_shader->GetProgram(), GLProgram::ATTRIBUTE_NAME_TEX_COORD);

	glVertexAttribPointer(m_positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
	glEnableVertexAttribArray(m_positionAttributeLocation);

	glVertexAttribPointer(m_ColorAttributeLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(m_ColorAttributeLocation);
	glVertexAttribPointer(m_TextureAttributeLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(m_TextureAttributeLocation);

	m_Texture1 = YTexture2D::create("src/Sample/Camera-Test/Texture/container.jpg");
	m_Texture2 = YTexture2D::create("src/Sample/Camera-Test/Texture/awesomeface.png");
	

	m_shader->SetInt(GLProgram::UNIFORM_NAME_TEXTURE1, 0);
	m_shader->SetInt(GLProgram::UNIFORM_NAME_TEXTURE2, 1);
	glBindVertexArray(0);

}

void TextureTest::onDraw(const glm::mat4* transform, uint32_t)
{
	m_shader->use();
	glBindVertexArray(m_VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture1->GetName());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_Texture2->GetName());

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	

}

