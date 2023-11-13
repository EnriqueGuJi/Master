#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleOpenGL;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleEditor;
class ModuleRender;
class ModuleProgram;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

    ModuleOpenGL* GetOpenGL() { return render; }
    ModuleWindow* GetWindow() { return window; }
    ModuleInput*  GetInput() { return input; }
    ModuleEditor* GetEditor() { return editor; }
    ModuleProgram* GetProgram() { return program; }


private:

    ModuleOpenGL* render = nullptr;
    ModuleWindow* window = nullptr;
    ModuleInput* input = nullptr;
    ModuleEditor* editor = nullptr;
    ModuleProgram* program = nullptr;

    std::list<Module*> modules;

};

extern Application* App;
