﻿#include "Application.h"
#include "ModuleOpenGL.h"
#include "ModuleProgram.h"
#include "ModuleRenderExercice.h"
#include "glew.h"
#include "ModuleRenderExercice.h"
#include "ModuleCamera.h"

ModuleRenderExercice::ModuleRenderExercice()
{

}

// Destructor
ModuleRenderExercice::~ModuleRenderExercice()
{

}

unsigned ModuleRenderExercice::CreateTriangleVBO()
{
	unsigned vbo;
	GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	 -0.5f, 0.5f, 0.0f
	};


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	return vbo;
}

unsigned ModuleRenderExercice::CreateTriangleEBO()
{
	unsigned ebo;
	unsigned indices[] =
	{
		0, 1, 2,
		0, 2, 3,
	};

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	return ebo;
}

void ModuleRenderExercice::RenderVBO(unsigned vbo, unsigned program)
{

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glEnableVertexAttribArray(0);
	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glUseProgram(program);

	glUniformMatrix4fv(0, 1, GL_TRUE, (GLfloat*)&App->GetCamera()->model);
	glUniformMatrix4fv(1, 1, GL_TRUE, (GLfloat*)&App->GetCamera()->view);
	glUniformMatrix4fv(2, 1, GL_TRUE, (GLfloat*)&App->GetCamera()->project);

	// 1 triangle to draw = 3 vertices
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

bool ModuleRenderExercice::Init()
{

	vbo = CreateTriangleVBO();
	ebo = CreateTriangleEBO();
	return true;
}

update_status ModuleRenderExercice::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRenderExercice::Update()
{

	RenderVBO(vbo, App->GetProgram()->programId);

	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercice::PostUpdate()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderExercice::CleanUp()
{
	glDeleteBuffers(1, &vbo);
	return true;
}
