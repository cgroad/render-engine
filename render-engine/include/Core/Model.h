#pragma once

#include <Core/Shader.h>
#include <iostream>
#include <vector>
#include <Core//Mesh.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <std_image.h>

class Model
{
public:
	Model();
	~Model();
	Model(const char* path);
	void Draw();
private:
	vector<Mesh> meshes;
	string directory = "resource/model";
	vector<TextureStruct> texture_loaded;

	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<TextureStruct> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
	unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);
};
