#pragma once
#include "Module.h"
#include "Globals.h"
#include "Math/float2.h"


#define NUM_MOUSE_BUTTONS 5
#define MAX_KEYS 300

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};
class ModuleInput : public Module
{
public:
	
	KeyState GetKey(int id) const;
	KeyState GetMouseButtonDown(int id) const;

	float2 mouseMotion;
	float2 mousePosition;
	float yWheel;

	KeyState* keyboard = nullptr;

	KeyState mouse_buttons[NUM_MOUSE_BUTTONS];

	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();

};