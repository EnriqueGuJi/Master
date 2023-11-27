#include "Application.h"
#include "ModuleModel.h"

#define TINYGLTF_IMPLEMENTATION /* Only in one of the includes */
#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_EXTERNAL_IMAGE
#include "tiny_gltf.h"

void Model::Load(const char* assetFileName)
{
	tinygltf::TinyGLTF gltfContext;
	tinygltf::Model model;
	std::string error, warning;
	bool loadOk = gltfContext.LoadASCIIFromFile(&model, &error, &warning, assetFileName);
	if (!loadOk)
	{
		LOG("Error loading %s: %s", assetFileName, error.c_str());
	}
}

ModuleModel::ModuleModel()
{

}

// Destructor
ModuleModel::~ModuleModel()
{

}

// Called before render is available
bool ModuleModel::Init()
{

	return true;
}

update_status ModuleModel::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleModel::Update()
{

	return UPDATE_CONTINUE;
}

update_status ModuleModel::PostUpdate()
{

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleModel::CleanUp()
{

	return true;
}