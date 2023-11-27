#pragma once

#include "Module.h"
#include "stb_image.h"
#include "tiny_gltf.h"
class ModuleModel : public Module
{
public:

	void Load(const char* assetFileName);

	
	ModuleModel();
	~ModuleModel();


	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

