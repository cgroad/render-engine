#pragma once

#include <core/ARE3D.h>
#include <Demo/Define.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Core/MathTool.h>
#include <Core/Camera.h>
#include <core/Cube.h>
#include <Core/Model.h>
#include <iostream>
#include <vector>
class AREDemo
{
public:
	AREDemo();
	~AREDemo();
	void Run();
	void keyPressHandle(int key, int scancode, int action, int mods);
private:
	bool init();
	void unInit();
	//resource related
	bool resInit();
	void resUninit();
	//game logic
	void update();
	//game render
	void render();

	static void framebufferSizeListener(GLFWwindow* window, int width, int height);
	static void mouseMoveListener(GLFWwindow* window, double xpos, double ypos);
	static void keyPressListener(GLFWwindow* win, int key, int scancode, int action, int mods);

private:
	GLFWwindow* window;
	bool running;
	Camera *camera;
	unsigned int VBO, VAO, EBO;
	float smileValue = 1;
	float scale = -1;
	MathTool *mathTool = new MathTool();
	vector<Cube *> cubes;
	Model *model;
};
