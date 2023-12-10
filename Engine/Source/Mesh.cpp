#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_EXTERNAL_IMAGE

#include "Application.h"
#include "ModuleOpenGL.h"
#include "ModuleProgram.h"
#include "ModuleRenderExercice.h"
#include "glew.h"
#include "ModuleRenderExercice.h"
#include "ModuleCamera.h"
#include "Mesh.h"
#include "ModuleModel.h"
#include "tiny_gltf.h"

void Mesh::Render()
{
	glBindVertexArray(vao);
	glUseProgram(App->GetProgram()->programId);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, App->GetModel()->textures[App->GetModel()->textures.size() - 1]);

	if (indCount > 0)
	{
		glDrawElements(GL_TRIANGLES, indCount, GL_UNSIGNED_INT, nullptr);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	}
}

void Mesh::Load(const tinygltf::Model model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive)
{
	const auto& itPos = primitive.attributes.find("POSITION"); // busca POSITION en el archivo gltf si esta entra en el IF
	const auto& itNor = primitive.attributes.find("NORMAL");
	const auto& itTex = primitive.attributes.find("TEXCOORD_0");
	
	// crear una variable para guardar el numero con el que compararemos el itPos
	int bufferSize = 0;

	if (itPos != primitive.attributes.end())
	{
		bufferSize += 3;
	}
	if (itNor != primitive.attributes.end())
	{
		bufferSize += 3;
	}
	if (itTex != primitive.attributes.end())
	{
		bufferSize += 2;
	}

	if (itPos != primitive.attributes.end())
	{
		const tinygltf::Accessor& posAcc = model.accessors[itPos->second]; 
		vertexCount = posAcc.count;
		SDL_assert(posAcc.type == TINYGLTF_TYPE_VEC3);
		SDL_assert(posAcc.componentType == GL_FLOAT);
		const tinygltf::BufferView& posView = model.bufferViews[posAcc.bufferView];
		const tinygltf::Buffer& posBuffer = model.buffers[posView.buffer];
		const unsigned char* bufferPos = &(posBuffer.data[posAcc.byteOffset + posView.byteOffset]);

		//solo puede estar creado 1 vez
		glGenBuffers(1, (GLuint*)&vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);// hay que bindear siempre el buffer despues de usar un genbuffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * bufferSize * posAcc.count, nullptr, GL_STATIC_DRAW); // hacer una funcion que detecte si estamos usando un valor de memoria que le pasamos, pasamos 3 con posiciones, otros 3 con normales, 2 mas con uv, tangentes otros 3. el sizeof debera detectar el numero total porque si le pasamos uno superior no cargara el modelo.
	
		float3* ptr = reinterpret_cast<float3*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
		for (size_t i = 0; i < posAcc.count; ++i)
		{
			ptr[i] = *reinterpret_cast<const float3*>(bufferPos);

			if (posView.byteStride > 0)	
			{
				bufferPos += posView.byteStride;
			}
			else
			{
				bufferPos += sizeof(float) * 3; // sizeof para que empize a contar en el siguientes vertice porque si no se queda en el 0.
			}
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}

	if (itTex != primitive.attributes.end())
	{
		const tinygltf::Accessor& posAcc = model.accessors[itTex->second];
		vertexCount = posAcc.count;
		SDL_assert(posAcc.type == TINYGLTF_TYPE_VEC2);
		SDL_assert(posAcc.componentType == GL_FLOAT);
		const tinygltf::BufferView& posView = model.bufferViews[posAcc.bufferView];
		const tinygltf::Buffer& posBuffer = model.buffers[posView.buffer];
		const unsigned char* bufferTex = &(posBuffer.data[posAcc.byteOffset + posView.byteOffset]);

		float2* ptr = reinterpret_cast<float2*>(reinterpret_cast<char*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY)) + vertexCount * sizeof(float) * 3);
		for (size_t i = 0; i < posAcc.count; ++i)
		{
			ptr[i] = *reinterpret_cast<const float2*>(bufferTex);

			if (posView.byteStride > 0)
			{
				bufferTex += posView.byteStride;
			}
			else
			{
				bufferTex += sizeof(float) * 2; // sizeof para que empize a contar en el siguientes vertice porque si no se queda en el 0.
			}
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}

	if (itNor != primitive.attributes.end())
	{
		const tinygltf::Accessor& posAcc = model.accessors[itNor->second];
		vertexCount = posAcc.count;
		SDL_assert(posAcc.type == TINYGLTF_TYPE_VEC3);
		SDL_assert(posAcc.componentType == GL_FLOAT);
		const tinygltf::BufferView& posView = model.bufferViews[posAcc.bufferView];
		const tinygltf::Buffer& posBuffer = model.buffers[posView.buffer];
		const unsigned char* bufferNor = &(posBuffer.data[posAcc.byteOffset + posView.byteOffset]);

		//hay que sumnar en bytes para que salte el PTR hasta los normals y que no se quede en las posiciones.

		float3* ptr = nullptr;

		if (itTex != primitive.attributes.end())
		{
			ptr = reinterpret_cast<float3*>(reinterpret_cast<char*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY)) + vertexCount * sizeof(float) * 5);
		}
		else
		{
			ptr = reinterpret_cast<float3*>(reinterpret_cast<char*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY)) + vertexCount * sizeof(float) * 3);
		}

		for (size_t i = 0; i < posAcc.count; ++i)
		{
			ptr[i] = *reinterpret_cast<const float3*>(bufferNor);

			if (posView.byteStride > 0)
			{
				bufferNor += posView.byteStride;
			}
			else
			{
				bufferNor += sizeof(float) * 3; // sizeof para que empize a contar en el siguientes vertice porque si no se queda en el 0.
			}
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
}

void Mesh::LoadEBO(const tinygltf::Model & model, const tinygltf::Mesh & mesh, const tinygltf::Primitive & primitive)
{
		if (primitive.indices >= 0)
		{
			const tinygltf::Accessor& indAcc = model.accessors[primitive.indices];
			indCount = indAcc.count;
			const tinygltf::BufferView& indView = model.bufferViews[indAcc.bufferView];
			const unsigned char* buffer = &(model.buffers[indView.buffer].data[indAcc.byteOffset + indView.byteOffset]);

			glGenBuffers(1, (GLuint*)&ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indAcc.count, nullptr, GL_STATIC_DRAW);

			unsigned int* ptr = reinterpret_cast<unsigned int*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));

			if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_INT)
			{
				const uint32_t* bufferInd = reinterpret_cast<const uint32_t*>(buffer);
				for (uint32_t i = 0; i < indCount; ++i) 
				{
					ptr[i] = bufferInd[i];
				}
			}
			if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT)
			{
				const uint16_t* bufferInd = reinterpret_cast<const uint16_t*>(buffer);
				for (uint16_t i = 0; i < indCount; ++i)
				{
					ptr[i] = bufferInd[i];
				}
			}
			if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_BYTE)
			{
				const uint8_t* bufferInd = reinterpret_cast<const uint8_t*>(buffer);
				for (uint8_t i = 0; i < indCount; ++i)
				{
					ptr[i] = bufferInd[i];
				}
			}
			glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		}

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * vertexCount));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 5 * vertexCount));
		glBindVertexArray(0);
}

void Mesh::CreateVAO()
{
	glGenVertexArrays(1, (GLuint*)&vao);
	glBindVertexArray(vao);
}