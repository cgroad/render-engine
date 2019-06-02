#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <core/Shader.h>
#include <Core/Texture.h>
#include <Core/Camera.h>
class Cube
{
public:
	Cube();
	~Cube();

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	void setShader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* texturePath);
	glm::mat4 getModelMatrix();
	void draw();
private:
	unsigned int VBO, VAO;
	Shader *shader;
	Texture* texture;
	Texture* texture2;
	Texture* texture3;
	Camera *camera = Camera::getInstance();
};