#pragma once

#include <glm\glm.hpp>
#include <glad\glad.h>
#include <iostream>
#include <vector>
#include <Core/Shader.h>
#include <Core/Camera.h>
using namespace std;
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct TextureStruct
{
	unsigned int id;
	string type;
	string path;
};

class Mesh
{
public:
	Mesh();
	~Mesh();
	//���񶥵�����
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<TextureStruct> textures;
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<TextureStruct> textures);
	void Draw();
	void setShader(const GLchar* vertexPath, const GLchar* fragmentPath);
private:
	unsigned int VAO, VBO, EBO;
	Shader *shader;
	Camera *camera;
	void setupMesh();
	glm::mat4 getModelMatrix();
};
