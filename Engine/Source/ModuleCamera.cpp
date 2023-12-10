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

float4x4 ModuleCamera::LookAt(float3 cameraPos, float3 targetPos, float3 upVector) // Matrix and variables like PDF Game_Camera, to do LookAt funct. CameraPos is the position of the frustum(transform), targetPos the target is looking. 
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
			frustum.pos -= frustum.up * camSpeed; // we get the pos of frustum and less or sum the frustum.y 
			if (App->GetInput()->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
			{
				frustum.pos -= frustum.up * camSpeed * duplicateSpeed;
			}	
		}
		
		if (App->GetInput()->GetKey(SDL_SCANCODE_E) == KEY_REPEAT)
		{
			frustum.pos += frustum.up * camSpeed;
			if (App->GetInput()->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
			{
				frustum.pos += frustum.up * camSpeed * duplicateSpeed;
			}
		}
		
		if (App->GetInput()->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) 
		{
			frustum.pos += frustum.front * camSpeed; // we get the pos of frustum and less or sum the frustum.z
			if (App->GetInput()->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
			{
				frustum.pos += frustum.front * camSpeed * duplicateSpeed;
			}
		}
		
		if (App->GetInput()->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			frustum.pos -= frustum.front * camSpeed;
			if (App->GetInput()->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
			{
				frustum.pos -= frustum.front * camSpeed * duplicateSpeed;
			}
		}
		
		if (App->GetInput()->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			frustum.pos -= frustum.WorldRight() * camSpeed; //we get the pos of frustum and less or sum the frustum.X world coords
			if (App->GetInput()->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
			{
				frustum.pos -= frustum.WorldRight() * camSpeed * duplicateSpeed;
			}
		}
		
		if (App->GetInput()->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			frustum.pos += frustum.WorldRight() * camSpeed;
			if (App->GetInput()->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
			{
				frustum.pos += frustum.WorldRight() * camSpeed * duplicateSpeed;
			}
		}
}

void ModuleCamera::PanMovement() 
{
	if (App->GetInput()->GetMouseButtonDown(SDL_BUTTON_MIDDLE) == KEY_REPEAT)
	{
		if (App->GetInput()->mouseMotion.y !=0) 
		{
			frustum.pos += frustum.up * App->GetInput()->mouseMotion.y * camSpeed; // with mouseMotion (sdlEventMouse) can move only in x and y coords 
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
			frustum.pos += frustum.front * camSpeed; //exactly like W and S movement
		}
		if (App->GetInput()->yWheel < 0)
		{
			frustum.pos -= frustum.front * camSpeed;
		}
}

void ModuleCamera::RotationInX()
{
	float3x3 rotationDeltaMatrix = float3x3::RotateY(DegToRad(App->GetInput()->mousePosition.x - lastPosition.x) * rotateSpeed); //funtion of PDF Game_Camera, but set a delta value, 
	float3 oldFront = frustum.front.Normalized();																				 //RotateY(degree to radians) and get the mouse pos
	frustum.front = rotationDeltaMatrix.MulDir(oldFront);																		 //lastpos and subtract both * sens.
	float3 oldUp = frustum.up.Normalized();
	frustum.up = rotationDeltaMatrix.MulDir(oldUp);
}

void ModuleCamera::RotationInY()
{
	float3x3 rotationDeltaMatrix = float3x3::RotateAxisAngle(frustum.WorldRight(), DegToRad(App->GetInput()->mousePosition.y - lastPosition.y) * rotateSpeed);  //the same of X but in that case we need the AxisAngle and use
	float3 oldFront = frustum.front.Normalized();																												 //the frustum.WorldRight()
	frustum.front = rotationDeltaMatrix.MulDir(oldFront);																								 
	float3 oldUp = frustum.up.Normalized();
	frustum.up = rotationDeltaMatrix.MulDir(oldUp);
}

void ModuleCamera::Orbit()
{
	if ((App->GetInput()->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT) && (App->GetInput()->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT))
	{
		float3 camFocusVector = frustum.pos;
		if (App->GetInput()->mouseMotion.x != 0)
		{
			float3x3 rotationOrbitX = float3x3::RotateAxisAngle(frustum.up, DegToRad(App->GetInput()->mousePosition.x - lastPosition.x) * rotateSpeed);
			camFocusVector = rotationOrbitX.Mul(camFocusVector);
		}

		if (App->GetInput()->mouseMotion.y != 0)
		{
			float3x3 rotationOrbitY = float3x3::RotateAxisAngle(frustum.WorldRight(), DegToRad(App->GetInput()->mousePosition.y - lastPosition.y) * rotateSpeed);  //the same of X but in that case we need the AxisAngle and use
			camFocusVector = rotationOrbitY.Mul(camFocusVector);
		}
		frustum.pos = camFocusVector;
		LookAtPoint(float3(0.0f, 0.0f, 0.0f));
	}
}

void ModuleCamera::RotationMovement()
{
	if ((App->GetInput()->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_REPEAT)) //to organize the rotation() method
	{
		if (App->GetInput()->mouseMotion.x !=0)
		{
			RotationInX();
		}
		if (App->GetInput()->mouseMotion.y !=0)
		{
			RotationInY();
		}
	}
}

void ModuleCamera::Center()
{
	if (App->GetInput()->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		LookAtPoint(float3(0.0f));
	}
}

void ModuleCamera::SetAspectRatio(float newAspectRatio)
{
	aspectRatio = newAspectRatio;
	frustum.verticalFov = 2.f * atanf(tanf(frustum.horizontalFov * 0.5f) * (1.0f / aspectRatio));
	project = frustum.ProjectionMatrix();
}

void ModuleCamera::SetFOV()
{
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * aspectRatio);
}

void ModuleCamera::LookAtPoint(const float3& point)
{
	float3 focusVec = (point - frustum.pos).Normalized();
	float3x3 lookMatrix = float3x3::LookAt(frustum.front, focusVec, frustum.up, float3(0.0f, 1.0f, 0.0f));
	frustum.front = lookMatrix.Mul(frustum.front).Normalized();
	frustum.up = lookMatrix.Mul(frustum.up).Normalized();
}

bool ModuleCamera::Init()
{
	lastPosition = App->GetInput()->mousePosition;

	aspectRatio = App->GetWindow()->width / App->GetWindow()->height;
	
	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3(0.f,1.f,5.f); // carrefull with this, check the Y pos.
	frustum.front = -float3::unitZ; //where the eye(camera) is looking
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;

	frustum.verticalFov = math::pi / 4.0f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * aspectRatio);

	project = frustum.ProjectionMatrix(); // Projection matrix

	model = float4x4::FromTRS(float3(0.0f, 0.0f, 0.0f), //Model matrix
			float4x4::RotateZ(0.f),
			float3(1.0f, 1.0f, 1.0f));

	return true;
}

update_status ModuleCamera::PreUpdate()
{
	Orbit();
	CameraMovement();
	PanMovement();
	ZoomMovement();
	RotationMovement();
	Center();

	lastPosition = App->GetInput()->mousePosition; //check the last position of mouse

	view = LookAt(frustum.pos, frustum.front + frustum.pos, frustum.up).Inverted(); // Model view

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