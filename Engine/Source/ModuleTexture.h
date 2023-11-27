#pragma once

#include "Module.h"

class ModuleTexture : public Module
{
public:

	int baboonTex;

	int widthTex, heightTex, colorTex;

	int internalFormat, format, type;

	ModuleTexture();
	~ModuleTexture();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

