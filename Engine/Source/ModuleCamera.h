#pragma once
#include "Module.h"
#include "Math/float4x4.h"

class ModuleCamera :

    public Module
{
public:

	float aspectRatio;

	float4x4 project;
	float4x4 view;
	float4x4 model;

	ModuleCamera();
	~ModuleCamera();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

