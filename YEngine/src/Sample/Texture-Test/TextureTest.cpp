#include "TextureTest.h"

#include <glfw3.h>
#include "YRenderer.h"
#include "YLoadShader.h"


TextureTest::TextureTest()
	:m_shader(nullptr)
{

}

TextureTest::~TextureTest()
{

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
	m_shader = new YShader("./src/Shader/Triangle.vs", "./src/Shader/Triangle.fs");
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
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	m_shader->use();

//	glGetAttribLocation(m_shader->ID,"")
}

void TextureTest::onDraw(const glm::mat4* transform, uint32_t)
{

}

