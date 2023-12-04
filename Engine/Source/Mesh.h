#pragma once

#include "Module.h"
#include "ModuleModel.h"

class Mesh
{
public:

	int vertexCount;
	int vbo;
	int ebo;
	int vao;
	int indCount;

	void Render();
	void Load(const tinygltf::Model model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
	void LoadEBO(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
	void CreateVAO();
	void Draw();


};

