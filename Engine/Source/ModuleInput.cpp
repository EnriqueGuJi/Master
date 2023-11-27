#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleOpenGL.h"
#include "SDL.h"
#include "ModuleEditor.h"
#include "backends/imgui_impl_sdl2.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"

ModuleInput::ModuleInput()
{
	keyboard = new KeyState[MAX_KEYS];
}

// Destructor
ModuleInput::~ModuleInput()
{
	delete keyboard;
}

KeyState ModuleInput::GetKey(int id) const // method to get key down
{
	return keyboard[id];
}

KeyState ModuleInput::GetMouseButtonDown(int id) const // method to get mouse button down
{
	return mouse_buttons[id - 1];
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
	mouseMotion = { 0, 0 }; //to update mouseMotion position every frame 
	yWheel = 0; //to update wheel button every frame 

    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);

        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;
            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED) //|| (sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED))
                   App->GetOpenGL()->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);	
				  // App->GetOpenGL()->WindowResized(App->GetCamera()->SetAspectRatio, App->GetCamera()->SetFOV);
                break;


			case SDL_MOUSEBUTTONDOWN: // to get event to mouse click
				mouse_buttons[sdlEvent.button.button - 1] = KEY_DOWN;
				break;

			case SDL_MOUSEBUTTONUP: // to get event to mouse click up
				mouse_buttons[sdlEvent.button.button - 1] = KEY_UP;
				break;

			case SDL_MOUSEMOTION: // to get event to mouse motion
				mouseMotion.x = sdlEvent.motion.xrel;
				mouseMotion.y = sdlEvent.motion.yrel;
				mousePosition.x = sdlEvent.motion.x;
				mousePosition.y = sdlEvent.motion.y;
				break;

			case SDL_MOUSEWHEEL: // to get event to mouse wheel
				yWheel = sdlEvent.wheel.y;
				break;
        }
    }

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	for (int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
	{
		if (mouse_buttons[i] == KEY_DOWN)
			mouse_buttons[i] = KEY_REPEAT;

		if (mouse_buttons[i] == KEY_UP)
			mouse_buttons[i] = KEY_IDLE;
	}

	if (GetKey(SDL_SCANCODE_ESCAPE) == KEY_REPEAT) 
	{
		return UPDATE_STOP;
	}

	//COMPROBAR SI LOS FOR VAN ARRIBA DEL WHILE

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
