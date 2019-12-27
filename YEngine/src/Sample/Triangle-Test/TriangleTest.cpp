#define GLEW_STATIC
#include "glew.h"
#include "TriangleTest.h"
#include "YRenderer.h"
#include "YLoadShader.h"

#include <glfw3.h>
#include "GLProgram.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
TriangleTest::TriangleTest()
	:m_shader(nullptr)
	,topColor(0.0f, 0.0f, 1.0f)
	,bottomLeftColor(1.0f, 0.0f, 0.0f)
	,bottomRightColor(0.0f, 1.0f, 0.0f)
{
	
}

TriangleTest::~TriangleTest()
{
	delete m_shader;
}

TriangleTest* TriangleTest::create()
{
	TriangleTest* res = new (std::nothrow)TriangleTest;
	if (res&&res->init())
	{
		return res;
	}
	delete res;
	res = nullptr;
	return nullptr;
}

void TriangleTest::draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags)
{
	glm::mat4 value = transform;
	m_customCommand.init(1);
	m_customCommand.func = std::bind(&TriangleTest::onDraw, this,&transform,flags);
	m_customCommand.setTransparent(false);
	m_customCommand.set3D(true);
	renderer->addCommand(&m_customCommand);
}

bool TriangleTest::init()
{
	m_shader = new YShader("./src/Shader/Triangle.vert","./src/Shader/Triangle.frag");
	initBuffers();
	return true;
}

void TriangleTest::initBuffers()
{
	float vertices[] = {
		0.5f, -0.5f, 0.0f, bottomRightColor.x,bottomRightColor.y,bottomRightColor.z, // bottom right
		-0.5f, -0.5f, 0.0f,  bottomLeftColor.x,bottomLeftColor.y,bottomLeftColor.z,// bottom left
		0.0f,  0.5f, 0.0f , topColor.x,topColor.y,topColor.z // top 
	};
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	m_shader->use();
	unsigned int pos = glGetAttribLocation(m_shader->GetProgram(), GLProgram::ATTRIBUTE_NAME_POSITION);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
	//glBindVertexArray(0);
}

void TriangleTest::onDraw(const glm::mat4* transform, uint32_t)
{
	float vertices[] = {
		0.5f, -0.5f, 0.0f, bottomRightColor.x,bottomRightColor.y,bottomRightColor.z, // bottom right
		-0.5f, -0.5f, 0.0f,  bottomLeftColor.x,bottomLeftColor.y,bottomLeftColor.z,// bottom left
		0.0f,  0.5f, 0.0f , topColor.x,topColor.y,topColor.z // top 
	};
    ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	//ImGui::NewFrame();
	ImGui::Begin("Triangle Vertex Color",0 , ImGuiWindowFlags_MenuBar);
	ImGui::Text("This is some useful text.");
	ImGui::ColorEdit3("TopColor",(float*)&topColor);
	ImGui::ColorEdit3("BottomLeftColor", (float*)&bottomLeftColor);
	ImGui::ColorEdit3("BottonRightColor", (float*)&bottomRightColor);
	ImGui::End();

	m_shader->use();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	m_shader->use();
	unsigned int pos = glGetAttribLocation(m_shader->GetProgram(), GLProgram::ATTRIBUTE_NAME_POSITION);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glDrawArrays(GL_TRIANGLES, 0, 3);
//	ImGui::Render();
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

