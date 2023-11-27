#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleOpenGL;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleEditor;
class ModuleRenderExercice;
class ModuleProgram;
class ModuleCamera;
class ModuleDebugDraw;
class ModuleTexture;

class Application

{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

    ModuleRenderExercice* GetRenderExercice() { return renderExercice; }
    ModuleOpenGL* GetOpenGL() { return render; }
    ModuleWindow* GetWindow() { return window; }
    ModuleInput*  GetInput() { return input; }
    ModuleEditor* GetEditor() { return editor; }
    ModuleProgram* GetProgram() { return program; }
    ModuleCamera* GetCamera() { return camera; }
    ModuleDebugDraw* GetDebugDraw() { return debugDraw; }
    ModuleTexture* GetTexture() { return texture; }


private:
    ModuleRenderExercice* renderExercice = nullptr;
    ModuleOpenGL* render = nullptr;
    ModuleWindow* window = nullptr;
    ModuleInput* input = nullptr;
    ModuleEditor* editor = nullptr;
    ModuleProgram* program = nullptr;
    ModuleCamera* camera = nullptr;
    ModuleDebugDraw* debugDraw = nullptr;
    ModuleTexture* texture = nullptr;

    std::list<Module*> modules;

};

extern Application* App;
