#pragma once
#include "Module.h"
#include "Math/float4x4.h"
#include "Math/float3.h"
#include "Geometry/Frustum.h"
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
	const float rotateSpeed = 0.05;
	const float camSpeed = 0.01f;
	const float duplicateSpeed = 3.f;

	float4x4 LookAt(float3 cameraPos, float3 targetPos, float3 upVector);

	//Unity scene movements
	void CameraMovement();
	void PanMovement();
	void ZoomMovement();
	void RotationMovement();
	void Orbit();

	//rotate Y,X methods
	void RotationInX();
	void RotationInY();
	void LookAtPoint(const float3& point);
	void Center();

	void SetFOV();
	void SetAspectRatio(float newAspectRatio);

	ModuleCamera();
	~ModuleCamera();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

