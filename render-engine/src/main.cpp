#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Core/MathTool.h>
#include <Core/Camera.h>
#include <core/Cube.h>
#include <vector>
void CreateHelloWindow();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);
void prepareRenderData();
void processRender();
unsigned int VBO, VAO, EBO;
float smileValue = 1;
float scale = -1;
MathTool *mathTool = new MathTool();
Camera *camera = Camera::getInstance();
vector<Cube *> cubes(10);

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

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
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD");
		return;
	}

	glViewport(0, 0, 1136, 640);
	glEnable(GL_DEPTH_TEST);
	prepareRenderData();
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		processRender();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	std::cout << xpos << "  " << ypos << std::endl;
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
	float cameraSpeed = 0.02f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->CameraPos += camera->CameraDir * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->CameraPos -= camera->CameraDir * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->CameraPos -= glm::normalize(glm::cross(camera->CameraUp, camera->CameraDir)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->CameraPos += glm::normalize(glm::cross(camera->CameraUp, camera->CameraDir)) * cameraSpeed;
	}
}

void  prepareRenderData()
{
	for (int i = 0; i < cubes.size(); i++)
	{
		cubes[i] = new Cube();
		cubes[i]->position = cubePositions[i];
		cubes[i]->setShader("resource/shader/vertex_demo.shader", "resource/shader/fragment_demo.shader", "resource/texture/t1.png");
	}
}

void processRender()
{
	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for (int i=0;i< cubes.size();i++)
	{
		if (cubes[i] != NULL)
		{
			cubes[i]->draw();
		}
	}
}

