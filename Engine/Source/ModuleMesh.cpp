#include "Application.h"
#include "ModuleOpenGL.h"
#include "ModuleProgram.h"
#include "ModuleRenderExercice.h"
#include "glew.h"
#include "ModuleRenderExercice.h"
#include "ModuleCamera.h"
#include "ModuleMesh.h"

//oid ModuleMesh::Render()
//
//	glUseProgram(program);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3 + sizeof(float) * 2, (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 3 + sizeof(float) * 2, (void*)(sizeof(float) * 3));
//	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
//
//
//oid ModuleMesh::Load(const Model& model, const Mesh& mesh, const Primitive& primitive)
//
//	const auto& itPos = primitive.attributes.find("POSITION");
//	if (itPos != primitive.attributes.end())
//	{
//		const Accessor& posAcc = model.accessors[itPos->second];
//		SDL_assert(posAcc.type == TINYGLTF_TYPE_VEC3);
//		SDL_assert(posAcc.componentType == GL_FLOAT);
//		const BufferView& posView = model.bufferViews[posAcc.bufferView];
//		const Buffer& posBuffer = model.buffers[posView.buffer];
//		const unsigned char* bufferPos = &(posBuffer.data[posAcc.byteOffset + posView.byteOffset]);
//		glGenBuffers(1, &vbo);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * posAcc.count, nullptr, GL_STATIC_DRAW);
//		float3* ptr = reinterpret_cast<float3*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
//		for (size_t i = 0; i < posAcc.count; ++i)
//		{
//			ptr[i] = *reinterpret_cast<const float3*>(bufferPos);
//			bufferPos += posView.byteStride;
//		}
//		glUnmapBuffer(GL_ARRAY_BUFFER);
//	}
//