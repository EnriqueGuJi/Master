#pragma once

#include "Module.h"

class Application;
struct ImGuiIO;

class ModuleEditor : public Module
{
public:
	
	ModuleEditor();
	~ModuleEditor();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:

	ImGuiIO* io;
};
