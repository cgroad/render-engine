#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Core/Shader.h>
#include <Core/Texture.h>
#include <Core/MathTool.h>
void CreateHelloWindow();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void prepareRenderData();
void processRender();
unsigned int VBO, VAO, EBO;
Texture* texture;
Texture* textureSmile;
Shader* demoShader;
float smileValue = 1;
float scale = -1;
MathTool *mathTool = new MathTool();

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	CreateHelloWindow();

	return 0;
}

void CreateHelloWindow()
{
	GLFWwindow* window = glfwCreateWindow(1136, 640, "LearOpenGL", NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to create GLFW window");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD");
		return;
	}

	glViewport(0, 0, 1136, 640);
	prepareRenderData();
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		processRender();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void  prepareRenderData()
{
	float vertices[] = {
//	------位置------ ----------颜色----------- -------纹理坐标------
	0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 1.0f,   // 顶点 红色
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.0f, // 右下角 绿色
	-0.5f, -0.5f, 0.0f,0.0f, 0.0f, 1.0f, 0.5f, 0.0f, 0.0f // 左下角 蓝色
	};

	unsigned int indices[] = { // 注意索引从0开始! 
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	int attributesNum;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attributesNum);

	texture = new Texture("resource/texture/myFamily.jpg", GL_TEXTURE0, GL_RGB);
	textureSmile = new Texture("resource/texture/smile.png", GL_TEXTURE1, GL_RGBA);
	demoShader = new Shader("resource/shader/vertex_demo.shader", "resource/shader/fragment_demo.shader");
}

void processRender()
{
	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	texture->use();
	textureSmile->use();
	demoShader->use();

	demoShader->setInt("myTexture1", 0);
	demoShader->setInt("myTexture2", 1);
	demoShader->setMat4("transform", mathTool->getTestMat4());
	//让笑脸眼神动起来
	if (smileValue>=1)
	{
		scale = -1;
	}
	if (smileValue <= 0.8)
	{
		scale = 1;
	}
	smileValue += scale * 0.0001;
	demoShader->setFloat("smileValue", smileValue);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

