#pragma once

#include "Module.h"


class Mesh;

//revisar namespace
namespace tinygltf
{
	class Model;
}

class ModuleModel : public Module
{
public:

	void Load(const char* assetFileName);
	void LoadMaterials(const tinygltf::Model& srcModel);

	std::vector<unsigned int> textures;

	ModuleModel();
	~ModuleModel();

	Mesh* mesh = nullptr;

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

