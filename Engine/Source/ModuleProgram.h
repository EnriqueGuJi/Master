#pragma once
#include "Module.h"

class ModuleProgram : public Module
{
public:  
	
	unsigned compileVertex;
	unsigned compileFragment;
	unsigned programId;


	ModuleProgram();
	~ModuleProgram();

	char* LoadingShader(const char* shader_file_name);
	unsigned CompileShader(unsigned type, const char* source);
	unsigned CreateProgram(unsigned vtx_shader, unsigned frg_shader);


	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

