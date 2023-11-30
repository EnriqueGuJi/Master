#pragma once

#include "Module.h"
#include "SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	int width;
	int height;

	ModuleWindow();
	~ModuleWindow();

	bool Init();
	bool CleanUp();

	//The window we'll be rendering to
	SDL_Window* window = nullptr;

	//The surface contained by the window
	SDL_Surface* screen_surface = nullptr;
};