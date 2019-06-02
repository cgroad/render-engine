#include "Core/Mesh.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<TextureStruct> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	camera = Camera::getInstance();
	setupMesh();
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	//顶点位置
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
	//顶点法线
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
	//顶点纹理坐标
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

void Mesh::setShader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	shader = new Shader(vertexPath, fragmentPath);
}

void Mesh::Draw()
{
	glBindVertexArray(VAO);
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		string number;
		string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);
		shader->setMat4("model", getModelMatrix());
		shader->setMat4("view", camera->GetViewMatrix());
		shader->setMat4("projection", camera->GetProjectionMatrix());
		shader->setInt((name + number).c_str(), i);
		shader->use();
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


glm::mat4 Mesh::getModelMatrix()
{
	glm::mat4 modelMat4 = glm::mat4(1.0f);
	modelMat4 = glm::translate(modelMat4, glm::vec3(0.0f, -5.0f, -25.0f));
	modelMat4 = glm::rotate(modelMat4, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMat4 = glm::rotate(modelMat4, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMat4 = glm::rotate(modelMat4, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//modelMat4 = glm::scale(modelMat4, glm::vec3(1.2f, 2.0f, 1.0f));
	return modelMat4;
}