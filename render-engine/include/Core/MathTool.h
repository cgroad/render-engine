#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
class MathTool
{
public:
	MathTool();
	~MathTool();
	void test();
	glm::mat4 getTestMat4();
	float getPercent(int loopSecond);
private:

};