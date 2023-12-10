#include "ModuleProgram.h"
#include <windows.h>
#include "glew.h"

ModuleProgram::ModuleProgram()
{

}

// Destructor
ModuleProgram::~ModuleProgram()
{

}

char* ModuleProgram::LoadingShader(const char* shader_file_name) // To load the data of shader
{
		
		char* data = nullptr;
		FILE* file = nullptr;

		fopen_s(&file, shader_file_name, "rb");
		if (file)
		{
			fseek(file, 0, SEEK_END);
			int size = ftell(file);
			data = (char*)malloc(size + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, size, file);
			data[size] = 0;
			fclose(file);
		}

		return data;
}

unsigned ModuleProgram::CompileShader(unsigned type, const char* source) // To compile the shader
{ 
	unsigned shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &source, 0);
	glCompileShader(shader_id);

	int res = GL_FALSE;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetShaderInfoLog(shader_id, len, &written, info);
			LOG("Log Info: %s", info);
			free(info);
		}
	}
	return shader_id;

}

unsigned ModuleProgram::CreateProgram(unsigned vtx_shader, unsigned frg_shader) // For linking fragment and vertex shader
{
	unsigned program_id = glCreateProgram();
	glAttachShader(program_id, vtx_shader);
	glAttachShader(program_id, frg_shader);
	glLinkProgram(program_id);
	int res;
	glGetProgramiv(program_id, GL_LINK_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetProgramInfoLog(program_id, len, &written, info);
			LOG("Program Log Info: %s", info);
			free(info);
		}
	}
	glDeleteShader(vtx_shader);
	glDeleteShader(frg_shader);
	return program_id;

}

bool ModuleProgram::Init()
{
	const char* vertexData;
	const char* fragmentData;

	//First step to load the shaders, we need to write manually the path
	vertexData = LoadingShader("vertexShader.glsl");
	fragmentData = LoadingShader("fragmentShader.glsl");

	//Second step, we need to pass the variables vertexData, and fragmentData from before
	compileVertex = CompileShader(GL_VERTEX_SHADER, vertexData);
	compileFragment = CompileShader(GL_FRAGMENT_SHADER, fragmentData);

	//Last step, we use programID to pass to the RenderVBO method in renderExercice to draw the triangle, and pass the other 2 variable that contains frag and vertex compilated
	programId = CreateProgram(compileVertex, compileFragment);

	return true;
}

update_status ModuleProgram::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleProgram::Update()
{

	return UPDATE_CONTINUE;
}

update_status ModuleProgram::PostUpdate()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleProgram::CleanUp()
{
	return true;
}
