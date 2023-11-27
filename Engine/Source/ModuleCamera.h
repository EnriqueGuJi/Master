#pragma once
#include "Module.h"
#include "Math/float4x4.h"
#include "Math/float3.h"
#include "MathGeoLib.h"
#include <SDL.h>

class ModuleCamera : public Module
{
public:

	float aspectRatio;

	float4x4 project; 
	float4x4 view;
	float4x4 model;

	float2 lastPosition; // last pos of mouseMov

	Frustum frustum;
	float rotateSpeed = 0.05;
	float camSpeed = 0.1f;

	float4x4 LookAt(float3 cameraPos, float3 targetPos, float3 upVector);

	//Unity scene movements
	void CameraMovement();
	void PanMovement();
	void ZoomMovement();
	void RotationMovement();
	
	//rotate Y,X methods
	void RotationInX();
	void RotationInY();

	void SetFOV();
	void SetAspectRatio();

	ModuleCamera();
	~ModuleCamera();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

