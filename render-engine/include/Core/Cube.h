#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <core/Shader.h>
#include <Core/Texture.h>
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

	Camera *camera = Camera::getInstance();
};

Cube::Cube()
{
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


}
void Cube::setShader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* texturePath)
{
	shader = new Shader(vertexPath, fragmentPath);
	texture = new Texture(texturePath, GL_TEXTURE0, GL_RGB);
}

glm::mat4 Cube::getModelMatrix()
{
	glm::mat4 modelMat4 = glm::mat4(1.0f);
	modelMat4 = glm::translate(modelMat4, position);
	modelMat4 = glm::rotate(modelMat4, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMat4 = glm::rotate(modelMat4, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMat4 = glm::rotate(modelMat4, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	//modelMat4 = glm::scale(modelMat4, glm::vec3(1.2f, 2.0f, 1.0f));
	return modelMat4;
}

void Cube::draw()
{
	texture->use();
	shader->use();
	shader->setInt("myTexture1", 0);
	shader->setMat4("model", getModelMatrix());
	shader->setMat4("view", camera->GetViewMatrix());
	shader->setMat4("projection", camera->GetProjectionMatrix()); 
	shader->setVec3("lightColor", camera->GetLightColor());
	shader->setVec3("lightPos", camera->GetLightPos());
	shader->setVec3("viewPos", camera->CameraPos);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

Cube::~Cube()
{
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	VAO = 0;
	VBO = 0;
	texture = nullptr;
	shader = nullptr;
	camera = NULL;
}