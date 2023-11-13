#include "Globals.h"
#include "Application.h"
#include "ModuleOpenGL.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "GL/glew.h"
#include "ModuleEditor.h"
#include "ModuleProgram.h"

ModuleOpenGL::ModuleOpenGL()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // desired version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits
}

// Destructor
ModuleOpenGL::~ModuleOpenGL()
{

}

// Called before render is available
bool ModuleOpenGL::Init()
{
	LOG("Creating Renderer context");

	SDL_GL_CreateContext(App->GetWindow()->window);

	// � check for errors
	LOG("Using Glew %s", glewGetString(GLEW_VERSION));
	LOG("Vendor: %s", glGetString(GL_VENDOR));
	LOG("Renderer: %s", glGetString(GL_RENDERER));
	LOG("OpenGL version supported %s", glGetString(GL_VERSION));
	LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		LOG("Error initializing GLEW: %s", glewGetErrorString(err));
		return false;
	}

	int windowWidth, windowHeight;

	SDL_GetWindowSize(App->GetWindow()->window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);


	// Configurar los datos de los v�rtices del tri�ngulo
	GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	 -0.5f, 0.5f, 0.0f 
	};

	unsigned indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);\

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); // set vbo active
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}

update_status ModuleOpenGL::PreUpdate()
{
	glClearColor(0.1f, 0.1f, 0.43f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(App->GetProgram()->programId);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleOpenGL::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleOpenGL::PostUpdate()
{
    SDL_GL_SwapWindow(App->GetWindow()->window);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleOpenGL::CleanUp()
{
	LOG("Destroying renderer");
	glDeleteBuffers(1, &vbo);
	SDL_GL_DeleteContext(App->GetOpenGL()->context);
	SDL_DestroyWindow(App->GetWindow()->window);
	SDL_Quit();

	//Destroy window

	return true;
}

void ModuleOpenGL::WindowResized(unsigned width, unsigned height)
{
	glViewport(0, 0, width, height);
}

