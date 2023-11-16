#pragma once
#include "Module.h"

class ModuleRenderExercice : public Module
{
public:

	unsigned vbo;
	unsigned ebo;

	ModuleRenderExercice();
	~ModuleRenderExercice();

	
	void RenderVBO(unsigned vbo, unsigned program);

	unsigned CreateTriangleVBO();
	unsigned CreateTriangleEBO();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

