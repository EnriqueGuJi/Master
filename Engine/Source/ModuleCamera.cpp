#include "Application.h"
#include "ModuleCamera.h"
#include "MathGeoLib.h"
#include "ModuleWindow.h"
#include "ModuleInput.h" 
#include "SDL.h"

ModuleCamera::ModuleCamera()
{

}

// Destructor
ModuleCamera::~ModuleCamera()
{

}

float4x4 ModuleCamera::LookAt(float3 cameraPos, float3 targetPos, float3 upVector) 
{
	float3 forward = (targetPos - cameraPos).Normalized();
	float3 right = forward.Cross(upVector).Normalized();
	float3 up = right.Cross(forward).Normalized();
	float3 position = cameraPos;

	float4x4 cameraMatrix =
	{
		right.x, up.x, -forward.x, position.x,
		right.y, up.y, -forward.y, position.y,
		right.z, up.z, -forward.z, position.z,
			0,    0,		0,			1

	};

	return cameraMatrix;
}

void ModuleCamera::CameraMovement()
	{
		if (App->GetInput()->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT)
		{
			frustum.pos -= frustum.up * camSpeed;
		}

		if (App->GetInput()->GetKey(SDL_SCANCODE_E) == KEY_REPEAT)
		{
			frustum.pos += frustum.up * camSpeed;
		}

		if (App->GetInput()->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) 
		{
			frustum.pos += frustum.front * camSpeed;
		}

		if (App->GetInput()->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			frustum.pos -= frustum.front * camSpeed;
		}

		if (App->GetInput()->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			frustum.pos -= frustum.WorldRight() * camSpeed;
		}

		if (App->GetInput()->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			frustum.pos += frustum.WorldRight() * camSpeed;
		}

	}

void ModuleCamera::PanMovement() 
{
	if (App->GetInput()->GetMouseButtonDown(SDL_BUTTON_MIDDLE) == KEY_REPEAT)
	{
		if (App->GetInput()->mouseMotion.y !=0) 
		{
			frustum.pos += frustum.up * App->GetInput()->mouseMotion.y * camSpeed;

		}
		if (App->GetInput()->mouseMotion.x != 0)
		{
			frustum.pos -= frustum.WorldRight() * App->GetInput()->mouseMotion.x * camSpeed;

		}
	}

}

void ModuleCamera::ZoomMovement()
{
	
		if (App->GetInput()->yWheel > 0)
		{
			frustum.pos += frustum.front * camSpeed;
		}
		if (App->GetInput()->yWheel < 0)
		{
			frustum.pos -= frustum.front * camSpeed;
		}

}

void ModuleCamera::RotationMovement(float angle, const float3& axis)
{
	if ((App->GetInput()->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_REPEAT))
	{
		if (App->GetInput()->mouseMotion.y != 0)
		{
			float3x3 rotationDeltaMatrix = float3x3::RotateY(DegToRad(App->GetInput()->mousePosition.x *= camSpeed));
			float3 oldFront = frustum.front.Normalized();
			frustum.front = rotationDeltaMatrix.MulDir(oldFront);
			float3 oldUp = frustum.up.Normalized();
			frustum.up = rotationDeltaMatrix.MulDir(oldUp);
		}
		//if (App->GetInput()->mouseMotion.y != 0)
		//{
		//	float3x3 rotationDeltaMatrix = float3x3::RotateX(DegToRad(App->GetInput()->mousePosition.y));
		//	float3 oldFront = frustum.front.Normalized();
		//	frustum.front = rotationDeltaMatrix.MulDir(oldFront);
		//	float3 oldUp = frustum.up.Normalized();
		//	frustum.up = rotationDeltaMatrix.MulDir(oldUp);
		//}
		
	}
	
}

bool ModuleCamera::Init()
{

	aspectRatio = App->GetWindow()->width / App->GetWindow()->height;

	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3(0.f,1.f,5.f);
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = math::pi / 4.0f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * aspectRatio);

	project = frustum.ProjectionMatrix();

	model = float4x4::FromTRS(float3(0.0f, 1.0f, 0.0f),
			float4x4::RotateZ(0.f),
			float3(1.0f, 1.0f, 1.0f));

	view = LookAt(frustum.pos, frustum.front, frustum.up).Inverted();

	return true;
}

update_status ModuleCamera::PreUpdate()
{
	view = LookAt(frustum.pos, frustum.front + frustum.pos, frustum.up).Inverted();

	CameraMovement();
	PanMovement();
	ZoomMovement();
	RotationMovement(rotationAngle, frustum.pos);

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