#include "Core/MathTool.h"
#include <sys/timeb.h>
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
	matrix = glm::translate(matrix, glm::vec3(0.5f, 0.5f, 0.0f));
	matrix = glm::rotate(matrix, glm::radians(360.0f * getPercent(5)), glm::vec3(0.0f, 1.0f, 0.0f));

	return matrix;
}

float MathTool::getPercent(int loopSecond)
{
	struct timeb tb;
	ftime(&tb);
	time_t milliSecond = tb.time * 1000 + tb.millitm;
	return (milliSecond % (loopSecond * 1000)) / (loopSecond * 1000.0f);
}