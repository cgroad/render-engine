#include "Core/Camera.h"
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
	return glm::vec3(0.0f, 3.0f, -3.0f);
}