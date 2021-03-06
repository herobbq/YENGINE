#include "FrameBufferTest.h"

#include "hfileinclude.h"
#include "YLoadShader.h"
#include "YRenderer.h"
#include "GLProgram.h"
#include "YTexture2D.h"
#include "YType.h"
#include "YDirector.h"
#include "GLView.h"
#include "YCamera.h"

GLsizei TexWidth = 800, TexHeight = 600;

float FrameBufferTest::m_fWindowWidth = 800;

float FrameBufferTest::m_fWindowHeight = 600;
FrameBufferTest::FrameBufferTest()
	:m_shader(nullptr)
	, m_Texture1(nullptr)
	, m_Texture2(nullptr)
	, m_shader1(nullptr)
	/*, m_flastY(0.0f)
	, m_flastX(0.0f)
	,m_bfirstMouse(true)*/
{

}

FrameBufferTest::~FrameBufferTest()
{
	delete m_shader;
}

FrameBufferTest* FrameBufferTest::create()
{
	FrameBufferTest* res = new (std::nothrow)FrameBufferTest;
	if (res&&res->init())
	{
		return res;
	}
	delete res;
	res = nullptr;
	return nullptr;
}

void FrameBufferTest::draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags)
{
	glm::mat4 value = transform;
	m_customCommand.init(1);
	m_customCommand.func = std::bind(&FrameBufferTest::onDraw, this, &transform, flags);
	m_customCommand.setTransparent(false);
	m_customCommand.set3D(true);
	renderer->addCommand(&m_customCommand);
}



bool FrameBufferTest::init()
{

	
	m_shader = new YShader("./src/Shader/FrameBuffer.vert", "./src/Shader/FrameBuffer.frag");
	m_shader1 = new YShader("./src/Shader/FrameBufferScreen.vert", "./src/Shader/FrameBufferScreen.frag");
	initBuffers();
	return true;
}

void FrameBufferTest::initBuffers()
{
	float cubeVertices[] = {
		// positions          // texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	
	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
							 // positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};
	float planeVertices[] = {
		// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	

	glVertexAttribPointer(GLProgram::LAYOUT_INDEX_POSITION, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
	glEnableVertexAttribArray(GLProgram::LAYOUT_INDEX_POSITION);

	
	glVertexAttribPointer(GLProgram::LAYOUT_INDEX_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(GLProgram::LAYOUT_INDEX_TEXCOORDS);
	glBindVertexArray(0);

	unsigned int _vbo;
	glGenVertexArrays(1, &m_quardVAO);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(m_quardVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	m_shader1->use();
	unsigned int pos,texcoord;
	pos = glGetAttribLocation(m_shader1->GetProgram(), GLProgram::ATTRIBUTE_NAME_POSITION);
	glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
	glEnableVertexAttribArray(pos);

	texcoord = glGetAttribLocation(m_shader1->GetProgram(), GLProgram::ATTRIBUTE_NAME_TEX_COORD);
	glVertexAttribPointer(texcoord, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(texcoord);
	
	glBindVertexArray(0);
	glGenVertexArrays(1, &m_planeVAO);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(m_planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	

	glVertexAttribPointer(GLProgram::LAYOUT_INDEX_POSITION, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
	glEnableVertexAttribArray(GLProgram::LAYOUT_INDEX_POSITION);

	glVertexAttribPointer(GLProgram::LAYOUT_INDEX_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(GLProgram::LAYOUT_INDEX_TEXCOORDS);
	glBindVertexArray(0);

	m_Texture1 = YTexture2D::create("src/Sample/FarmeBuffer-Test/Texture/container.jpg");
	m_Texture2 = YTexture2D::create("src/Sample/FarmeBuffer-Test/Texture/metal.png");
	m_shader1->SetInt("utexture", 0);
	glGenFramebuffers(1, &m_BUF);
	glBindFramebuffer(GL_FRAMEBUFFER, m_BUF);

	glGenTextures( 1, &m_FarmeTexture);
	glBindTexture(GL_TEXTURE_2D, m_FarmeTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TexWidth, TexHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_FarmeTexture, 0);
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, TexWidth, TexHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	glNamedFramebufferRenderbuffer(m_BUF, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);				  // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
}

void FrameBufferTest::onDraw(const glm::mat4* transform, uint32_t)
{
	//glfwSetInputMode(YDirector::GetInstance()->getGLwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::Begin("FrameBufferSize",0 , ImGuiWindowFlags_MenuBar);
	ImGui::DragFloat("FramerBufferWidth", &m_fWindowWidth,1.0f,0.0f,100000.0f);
	ImGui::DragFloat("FramerBufferHeight", &m_fWindowHeight, 1.0f, 0.0f, 100000.0f);
	ImGui::End();

	glBindFramebuffer(GL_FRAMEBUFFER, m_BUF);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, TexWidth, TexHeight);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(m_planeVAO);
	m_shader->use();
	m_shader->setMat4(GLProgram::UNIFORM_NAME_PROJECTION, YCamera::m_visitingCamera->getProjectionMatrix()); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	m_shader->setMat4(GLProgram::UNIFORM_NAME_VIEW, glm::translate(YCamera::m_visitingCamera->getViewMatrix(), glm::vec3(0.0, 0.0, -3.0)));
	m_shader->setMat4(GLProgram::UNIFORM_NAME_MODEL, glm::mat4(1));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture2->GetName());
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(m_VAO);
	m_shader->use();
	m_shader->setMat4(GLProgram::UNIFORM_NAME_PROJECTION, YCamera::m_visitingCamera->getProjectionMatrix()); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	m_shader->setMat4(GLProgram::UNIFORM_NAME_VIEW, glm::translate(YCamera::m_visitingCamera->getViewMatrix(), glm::vec3(0.0, 0.0, -3.0)));
	m_shader->setMat4(GLProgram::UNIFORM_NAME_MODEL, glm::mat4(1));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture1->GetName());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//glGenerateTextureMipmap(m_FarmeTexture);
	glBindVertexArray(0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);


//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0,m_fWindowWidth, m_fWindowHeight);

	m_shader1->use();
	glBindVertexArray(m_quardVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_FarmeTexture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glViewport(0, 0, YDirector::GetInstance()->getWinsize().width, YDirector::GetInstance()->getWinsize().height);
}










