#pragma once
#include "Module.h"
#include "SDL_surface.h"
#include "tiny_gltf.h"

// me falta alguna libreria

class ModuleMesh : public Module
{
public:

	void Render();

	//std::vector<Mesh> meshes;

	struct Primitive
	{
		std::map<std::string, int> attributes;
		int material{ -1 };
		int indices{ -1 };
	};

	struct Mesh
	{
		std::string name;
		std::vector<Primitive> primitives;
	};



	//void Load(const Model& model, const Mesh& mesh, const Primitive& primitive);
};

