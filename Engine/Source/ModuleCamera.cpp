#include "Application.h"
#include "ModuleCamera.h"
#include "MathGeoLib.h"
#include "ModuleWindow.h"


ModuleCamera::ModuleCamera()
{

}

// Destructor
ModuleCamera::~ModuleCamera()
{

}



bool ModuleCamera::Init()
{
	aspectRatio = App->GetWindow()->width / App->GetWindow()->height;

	Frustum frustum;
	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3(0.f,0.f,5.f);
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = math::pi / 4.0f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * aspectRatio);

	project = frustum.ProjectionMatrix();

	model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
			float4x4::RotateZ(pi / 4.0f),
			float3(2.0f, 1.0f, 1.0f));

	view = float4x4::LookAt(frustum.front, float3(0.f).Normalized(), frustum.up, float3::unitY);
	return true;
}

update_status ModuleCamera::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleCamera::Update()
{

	return UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleCamera::CleanUp()
{

	return true;
}
