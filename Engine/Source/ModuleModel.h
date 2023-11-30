#pragma once

#include "Module.h"

class Mesh;

class ModuleModel : public Module
{
public:

	void Load(const char* assetFileName);
	void LoadMaterials(const tinygltf::Model& srcModel);

	ModuleModel();
	~ModuleModel();

	Mesh* mesh;

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

