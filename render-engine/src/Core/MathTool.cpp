#include "Core/MathTool.h"
#include <sys/timeb.h>
#include <stdlib.h>
MathTool::MathTool()
{
}

MathTool::~MathTool()
{
}

void MathTool::test()
{
	glm::vec4 vec(1.0, 0.0, 0.0, 1.0);
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(1.0, 1.0, 0.0));
	vec = trans * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl;

}

glm::mat4 MathTool::getTestMat4()
{
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::rotate(matrix, glm::radians(360.0f * getPercent(5)), glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::translate(matrix, glm::vec3(0.5f, 0.5f, 0.0f));

	return matrix;
}

glm::mat4 MathTool::getMVPMat4(glm::vec3 translate = glm::vec3(0.0f, 0.0f, 0.0f))
{
	glm::mat4 modelMat4 = glm::mat4(1.0f);
	modelMat4 = glm::translate(modelMat4, translate);

	modelMat4 = glm::rotate(modelMat4, glm::radians(360.0f * getPercent(5)), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 viewMat4 = glm::mat4(1.0f);
	viewMat4 = glm::translate(viewMat4, glm::vec3(0.0f,0.0f,-4.0f));

	glm::mat4 projectionMat4 = glm::mat4(1.0f);
	projectionMat4 = glm::perspective(glm::radians(45.0f), 1136 / 640.0f, 0.1f, 100.0f);
	return projectionMat4 * viewMat4 * modelMat4;
}

float MathTool::getPercent(int loopSecond)
{
	struct timeb tb;
	ftime(&tb);
	time_t milliSecond = tb.time * 1000 + tb.millitm;
	return (milliSecond % (loopSecond * 1000)) / (loopSecond * 1000.0f);
}