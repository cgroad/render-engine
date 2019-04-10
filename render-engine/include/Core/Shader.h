#pragma once
#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Core/MathTool.h>
using namespace std;

class Shader
{
public:
	unsigned int ID;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void use();
	void setBool(const string &name, bool value);
	void setInt(const string &name, int value);
	void setFloat(const string &name, float value);
	void setColor(const string &name, float r, float g, float b, float a);
	void setMat4(const string &name, glm::mat4 matrix);
	void setVec3(const string &name, glm::vec3 value);
};
