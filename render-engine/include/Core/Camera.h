#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	glm::vec3 CameraPos = glm::vec3(0.0f, 1.0f, 1.5f);
	glm::vec3 CameraDir = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	glm::vec3 GetLightColor();
	glm::vec3 GetLightPos();
	static Camera *getInstance();
protected:

private:
	Camera();
	~Camera();
};