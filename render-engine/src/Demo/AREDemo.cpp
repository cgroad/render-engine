#include <Demo/AREDemo.h>

AREDemo::AREDemo()
{
}


AREDemo::~AREDemo()
{
}

void AREDemo::Run()
{
	//init demo related
	init();
	//init ARE
	areInit();
	//init resource
	resInit();
	//game loop
	while (!glfwWindowShouldClose(window))
	{
		update();
		render();

		glfwPollEvents();
		//frame end
		glfwSwapBuffers(window);
	}
	//uninit everything
	resUninit();
	unInit();
}

bool AREDemo::init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearOpenGL", NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to create GLFW window");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebufferSizeListener);
	glfwSetCursorPosCallback(window, mouseMoveListener);
	glfwSetKeyCallback(window, keyPressListener);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD");
		return false;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_DEPTH_TEST);

	return true;
}

bool AREDemo::resInit()
{
	camera = Camera::getInstance();

	cubes.push_back(new Cube());
	cubes[0]->position = glm::vec3(0.0f, 0.2f, -1.0f);
	cubes[0]->rotation = glm::vec3(20.0f, 35.0f, 0.0f);
	cubes[0]->setShader("resource/shader/vertex_demo.shader", "resource/shader/fragment_demo.shader", "resource/texture/box_diffuse.png");

	//µÆ¹â¶ÔÏó
	cubes.push_back(new Cube());
	cubes[1]->position = camera->GetLightPos();
	cubes[1]->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	cubes[1]->setShader("resource/shader/vertex_demo.shader", "resource/shader/fragment_for_light.shader", "resource/texture/box_diffuse.png");

	string modelPath = "resource/model/nanosuit.obj";
	model = new Model(modelPath.c_str());
	return true;
}

void AREDemo::framebufferSizeListener(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void AREDemo::mouseMoveListener(GLFWwindow* window, double xpos, double ypos)
{
	std::cout << xpos << "  " << ypos << std::endl;
}

void AREDemo::keyPressListener(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	AREDemo* demo = static_cast<AREDemo *>(glfwGetWindowUserPointer(win));
	demo->keyPressHandle(key, scancode, action, mods);
} 

void AREDemo::keyPressHandle(int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS)
	{
		return;
	}
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, true);
		break;
	case GLFW_KEY_F1:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case GLFW_KEY_F2:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	default:
		break;
	}
}

void AREDemo::update()
{
	float cameraSpeed = 0.002f;
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

void AREDemo::render()
{
	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (unsigned int i = 0; i < cubes.size(); i++)
	{
		if (cubes[i] != NULL)
		{
			cubes[i]->draw();
		}
	}
	model->Draw();
}

void AREDemo::unInit()
{
	glfwTerminate();
}

void AREDemo::resUninit()
{

}