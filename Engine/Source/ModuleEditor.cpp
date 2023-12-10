#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleWindow.h"
#include "ModuleOpenGL.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"
#include <Windows.h>

ModuleEditor::ModuleEditor()
{

}

// Destructor
ModuleEditor::~ModuleEditor()
{

}

bool ModuleEditor::Init()
{
	LOG("Creating ImGui context");
	ImGui::CreateContext();

	io = &(ImGui::GetIO());
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	//io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

	ImGui_ImplSDL2_InitForOpenGL(App->GetWindow()->window, App->GetOpenGL()->context);
	ImGui_ImplOpenGL3_Init("#version 460");

	return true;
}

update_status ModuleEditor::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleEditor::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	bool openWindow = true;
	static bool openAbout = false;

	if (openWindow)
	{
		if (ImGui::DockSpaceOverViewport(0, ImGuiDockNodeFlags_PassthruCentralNode))
		{
			if (openAbout)
			{
				if (ImGui::Begin("About", &openAbout))
				{
					ImGui::Separator();
					ImGui::Text("Our own Engine for assigment 1.");
					ImGui::Text("In this engine we can use various modules for manage our own Enigne,");
					ImGui::Text("(Camera, models, textures, imgui, OpenGL, shaders and more.");
					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();
					ImGui::Text("Libraries");
					ImGui::Text("OpenGL 4.6");
					ImGui::Text("SDL 2.0.16");
					ImGui::Text("Glew 2.1.0");
					ImGui::Text("MathGeoLib 1.5");
					ImGui::Text("DirectTex 201");
					ImGui::Text("TinyGLTF v2.8.10");
					ImGui::Text("ImGui v1.89.9");
					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();
					ImGui::Text("Licence");
					ImGui::Text("MIT License Copyright(c) 2023 Enrique Gutierrez Jimenez");
					ImGui::Separator();
					ImGui::Text("");
					ImGui::End();
				}
			}
			
			if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Quit"))
					{
						return UPDATE_STOP;
					}
					ImGui::EndMenu();

				}

				if (ImGui::BeginMenu("Help"))
				{
					if (ImGui::MenuItem("About"))
					{
						openAbout = true;
					}

					if (ImGui::MenuItem("GitHub"))
					{
						ShellExecute(NULL, "open", "https://github.com/EnriqueGuJi?tab=repositories", NULL, NULL, SW_SHOWNORMAL);
					}

					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			}
			//ImGui::Begin("Console");
			//ImGui::End();
			//ImGui::Begin("Inspector");
			//ImGui::End();
		}
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEditor::CleanUp()
{
	//Destroy window
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}