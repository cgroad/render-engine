#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	glm::vec3 CameraPos = glm::vec3(0.0f, 0.9f, 1.5f);
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

Camera::Camera()
{

}

Camera::~Camera()
{

}

Camera* Camera::getInstance()
{
	static Camera camera;
	return &camera;
}

glm::mat4 Camera::GetViewMatrix()
{
	glm::mat4 viewMat4 = glm::mat4(1.0f);
	viewMat4 = glm::lookAt(CameraPos, CameraPos + CameraDir, CameraUp);
	return viewMat4;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	glm::mat4 projectionMat4 = glm::mat4(1.0f);
	projectionMat4 = glm::perspective(glm::radians(45.0f), 1136 / 640.0f, 0.1f, 100.0f);
	return projectionMat4;
}

glm::vec3 Camera::GetLightColor()
{
	return glm::vec3(1.0f, 1.0f, 1.0f);
}

glm::vec3 Camera::GetLightPos()
{
	return glm::vec3(0.0f, 2.0f, -5.0f);
}