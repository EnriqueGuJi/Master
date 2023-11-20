#pragma once
#include "Module.h"
#include "Math/float4x4.h"
#include "Math/float3.h"
#include "MathGeoLib.h"
#include <SDL.h>

class ModuleCamera :

    public Module
{
public:

	float aspectRatio;

	float4x4 project;
	float4x4 view;
	float4x4 model;

	Frustum frustum;
	float camSpeed = 0.1f;
	float4x4 LookAt(float3 cameraPos, float3 targetPos, float3 upVector);

	void CameraMovement();
	void PanMovement();
	void ZoomMovement();

	ModuleCamera();
	~ModuleCamera();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

