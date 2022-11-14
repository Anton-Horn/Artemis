
#include "SpriteBatch.h"

#include "Rendering/OpenGL/OpenGLRenderer.h"
#include "Rendering/OpenGL/OpenGLVertexBuffer.h"
#include "Rendering/OpenGL/OpenGLShader.h"
#include "Rendering/OpenGL/OpenGLTexture.h"

#include "Core/Log.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Texture/BatchTextureManager.h"

#include "RenderingPipeline.h"



SpriteBatchData SpriteBatch::s_Data;

void SpriteBatch::Init()
{
	ART_LOG("[SpriteBatch] Started initializing");
		
	s_Data.TextureSlots = RenderingPipeline::GetData().Renderer->GetTextureSlots();

	VertexBufferSpec spec;
	spec.Attributes = { {VertexBufferDataType::FLOAT, 3}, {VertexBufferDataType::FLOAT, 4}, {VertexBufferDataType::FLOAT, 2}, {VertexBufferDataType::FLOAT, 1},{VertexBufferDataType::FLOAT, 1} };
	spec.BufferSize = (size_t)s_Data.MaxQuads * 4;
	spec.VertexSize = sizeof(Vertex);

	s_Data.VertexBuffer = VertexBuffer::Create(spec);

	s_Data.Shader = Shader::Create(Shader::LoadShaderSource({ PathType::Relative, "Assets/Shaders/EditorQuadVertexShader.vert" }).c_str(), Shader::LoadShaderSource({ PathType::Relative, "Assets/Shaders/EditorQuadFragmentShader.frag" }).c_str());

	Texture2DSpecification texture_spec;
	texture_spec.Width = 1;
	texture_spec.Height = 1;
	texture_spec.Data = nullptr;
	texture_spec.LoadFile = false;

	s_Data.Texture_0 = Texture2D::Create(texture_spec);
	s_Data.Texture_0->BindTextureUnit(0);

	s_Data.Samplers = new int[s_Data.TextureSlots];

	for (int i = 0; i < s_Data.TextureSlots; i++) {
		s_Data.Samplers[i] = i;
	}

	BatchTextureManager::Init(s_Data.TextureSlots);
	AT_LOG("[SpriteBatch] Finished initializing");

}
void SpriteBatch::Shutdown()
{
	BatchTextureManager::Shutdown();
	delete[] s_Data.Samplers;
}
void SpriteBatch::BeginFrame()
{
#ifdef AT_DEBUG
		s_Data.BatchCount = 0;
#endif 

}
void SpriteBatch::BeginBatch(const glm::mat4& ViewProjectionMatrix)
{
	s_Data.ViewProjectionMatrix = ViewProjectionMatrix;
	s_Data.VertexBuffer->Reset();
	BatchTextureManager::NewBatch();

#ifdef AT_DEBUG
		s_Data.BatchCount++;
#endif

}

void SpriteBatch::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Color& c)
{
	
	if (!s_Data.VertexBuffer->HasCapacity()) {
		EndBatch();
		BeginBatch(s_Data.ViewProjectionMatrix);
	}

	Vertex v1 = { pos.x, pos.y + size.y, 0.0f, c, 0.0f, 0.0f, 0.0f, 1.0f};
	Vertex v2 = { pos.x, pos.y, 0.0f, c, 0.0f, 0.0f, 0.0f, 1.0f};
	Vertex v3 = { pos.x + size.x, pos.y,0.0f, c, 0.0f, 0.0f, 0.0f, 1.0f};
	Vertex v4 = { pos.x + size.x, pos.y + size.y, 0.0f, c, 0.0f, 0.0f, 0.0f, 1.0f};

	s_Data.VertexBuffer->AddVertex(v1);
	s_Data.VertexBuffer->AddVertex(v2);
	s_Data.VertexBuffer->AddVertex(v3);
	s_Data.VertexBuffer->AddVertex(v4);
}
void SpriteBatch::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Color& c, float rotation, const glm::vec2& origin_offset) {

	if (!s_Data.VertexBuffer->HasCapacity()) {
		EndBatch();
		BeginBatch(s_Data.ViewProjectionMatrix);
	}

	glm::vec4 v1_Pos = glm::vec4(0.0f + origin_offset.x, size.y + origin_offset.y, 1.0f,1.0f);
	glm::vec4 v2_Pos = glm::vec4(0.0f + origin_offset.x, 0.0f + origin_offset.y, 1.0f, 1.0f);
	glm::vec4 v3_Pos = glm::vec4(size.x + origin_offset.x, 0.0f + origin_offset.y, 1.0f, 1.0f);
	glm::vec4 v4_Pos = glm::vec4(size.x + origin_offset.x, size.y, size.y + origin_offset.y, 1.0f);

	glm::mat4 rotation_transform = glm::mat4(1.0f);
	rotation_transform = glm::rotate(rotation_transform, rotation, glm::vec3(0.0f, 0.0f, 1.0f));

	v1_Pos = v1_Pos * rotation_transform;
	v2_Pos = v2_Pos * rotation_transform;
	v3_Pos = v3_Pos * rotation_transform;
	v4_Pos = v4_Pos * rotation_transform;

	v1_Pos += glm::vec4(pos.x, pos.y, 0.0f,0.0f);
	v2_Pos += glm::vec4(pos.x, pos.y, 0.0f, 0.0f);
	v3_Pos += glm::vec4(pos.x, pos.y, 0.0f, 0.0f);
	v4_Pos += glm::vec4(pos.x, pos.y, 0.0f, 0.0f);

	Vertex v1 = { v1_Pos.x, v1_Pos.y, 0.0f, c, 0.0f, 0.0f, 0.0f, 1.0f};
	Vertex v2 = { v2_Pos.x, v2_Pos.y, 0.0f, c, 0.0f, 0.0f, 0.0f, 1.0f};
	Vertex v3 = { v3_Pos.x, v3_Pos.y, 0.0f, c, 0.0f, 0.0f, 0.0f, 1.0f};
	Vertex v4 = { v4_Pos.x, v4_Pos.y, 0.0f, c, 0.0f, 0.0f, 0.0f, 1.0f};

	s_Data.VertexBuffer->AddVertex(v1);
	s_Data.VertexBuffer->AddVertex(v2);
	s_Data.VertexBuffer->AddVertex(v3);
	s_Data.VertexBuffer->AddVertex(v4);

}
void SpriteBatch::DrawQuad(const glm::vec2& pos, const glm::vec2& size, Ref<Texture2D> texture, float tiling_factor)
{

	if (!s_Data.VertexBuffer->HasCapacity() || BatchTextureManager::IsOccupied()) {
		EndBatch();
		BeginBatch(s_Data.ViewProjectionMatrix);
	}

	float result;
	if (!BatchTextureManager::CheckTexture(texture->GetRendererTexture(), &result)) {
		result = BatchTextureManager::AddTexture(texture->GetRendererTexture());
		texture->BindTextureUnit((int) result);
	}

	Color c = {1.0f, 1.0f, 1.0f, 1.0f};

	Vertex v1 = { pos.x, pos.y + size.y, 0.0f, c, 0.0f, 0.0f, result, tiling_factor};
	Vertex v2 = { pos.x, pos.y, 0.0f, c, 0.0f, 1.0f, result, tiling_factor};
	Vertex v3 = { pos.x + size.x, pos.y, 0.0f, c, 1.0f, 1.0f, result, tiling_factor};
	Vertex v4 = { pos.x + size.x, pos.y + size.y, 0.0f, c, 1.0f, 0.0f, result, tiling_factor};

	s_Data.VertexBuffer->AddVertex(v1);
	s_Data.VertexBuffer->AddVertex(v2);
	s_Data.VertexBuffer->AddVertex(v3);
	s_Data.VertexBuffer->AddVertex(v4);

}
void SpriteBatch::DrawQuad(const glm::vec2& pos, const glm::vec2& size, Ref<Texture2D> texture, float tiling_factor, float rotation, const glm::vec2& origin_offset)
{
	if (!s_Data.VertexBuffer->HasCapacity() || BatchTextureManager::IsOccupied()) {
		EndBatch();
		BeginBatch(s_Data.ViewProjectionMatrix);
	}

	float result;
	if (!BatchTextureManager::CheckTexture(texture->GetRendererTexture(), &result)) {
		result = BatchTextureManager::AddTexture(texture->GetRendererTexture());
		texture->BindTextureUnit((int)result);
	}

	Color c = { 1.0f,1.0f,1.0f,1.0f };

	glm::vec4 v1_Pos = glm::vec4(0.0f + origin_offset.x, size.y + origin_offset.y, 1.0f, 1.0f);
	glm::vec4 v2_Pos = glm::vec4(0.0f + origin_offset.x, 0.0f + origin_offset.y, 1.0f, 1.0f);
	glm::vec4 v3_Pos = glm::vec4(size.x + origin_offset.x, 0.0f + origin_offset.y, 1.0f, 1.0f);
	glm::vec4 v4_Pos = glm::vec4(size.x + origin_offset.x, size.y, size.y + origin_offset.y, 1.0f);

	glm::mat4 rotation_transform = glm::mat4(1.0f);
	rotation_transform = glm::rotate(rotation_transform, rotation, glm::vec3(0.0f, 0.0f, 1.0f));

	v1_Pos = v1_Pos * rotation_transform;
	v2_Pos = v2_Pos * rotation_transform;
	v3_Pos = v3_Pos * rotation_transform;
	v4_Pos = v4_Pos * rotation_transform;

	v1_Pos += glm::vec4(pos.x, pos.y, 0.0f, 0.0f);
	v2_Pos += glm::vec4(pos.x, pos.y, 0.0f, 0.0f);
	v3_Pos += glm::vec4(pos.x, pos.y, 0.0f, 0.0f);
	v4_Pos += glm::vec4(pos.x, pos.y, 0.0f, 0.0f);

	Vertex v1 = { v1_Pos.x, v1_Pos.y, 0.0f, c, 0.0f, 0.0f, result, tiling_factor};
	Vertex v2 = { v2_Pos.x, v2_Pos.y, 0.0f, c, 0.0f, 1.0f, result, tiling_factor};
	Vertex v3 = { v3_Pos.x, v3_Pos.y, 0.0f, c, 1.0f, 1.0f, result, tiling_factor};
	Vertex v4 = { v4_Pos.x, v4_Pos.y, 0.0f, c, 1.0f, 0.0f, result, tiling_factor};

	s_Data.VertexBuffer->AddVertex(v1);
	s_Data.VertexBuffer->AddVertex(v2);
	s_Data.VertexBuffer->AddVertex(v3);
	s_Data.VertexBuffer->AddVertex(v4);
}
void SpriteBatch::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& source_pos, const glm::vec2& source_size, Ref<Texture2D> texture)
{

	if (!s_Data.VertexBuffer->HasCapacity() || BatchTextureManager::IsOccupied()) {
		EndBatch();
		BeginBatch(s_Data.ViewProjectionMatrix);
	}

	float result;
	if (!BatchTextureManager::CheckTexture(texture->GetRendererTexture(), &result)) {
		result = BatchTextureManager::AddTexture(texture->GetRendererTexture());
		texture->BindTextureUnit((int)result);
	}

	Color c = { 1.0f,1.0f,1.0f,1.0f };

	int t_width = texture->GetWidth();
	int t_height = texture->GetHeight();

	float tx, ty, tw, th;

	tx = source_pos.x / t_width;
	ty = 1 - (source_pos.y / t_height);

	tw = source_size.x / t_width;
	th = source_size.y / t_height;

	glm::vec2 tc1 = glm::vec2(tx, ty + th);
	glm::vec2 tc2 = glm::vec2(tx, ty);
	glm::vec2 tc3 = glm::vec2(tx + tw, ty);
	glm::vec2 tc4 = glm::vec2(tx + tw, ty + th);


	Vertex v1 = { pos.x, pos.y + size.y, 0.0f, c, tc1.x, tc1.y, result, 1.0f};
	Vertex v2 = { pos.x, pos.y, 0.0f, c, tc2.x, tc2.y, result, 1.0f};
	Vertex v3 = { pos.x + size.x, pos.y, 0.0f, c, tc3.x, tc3.y, result, 1.0f};
	Vertex v4 = { pos.x + size.x, pos.y + size.y, 0.0f, c, tc4.x, tc4.y, result, 1.0f};

	s_Data.VertexBuffer->AddVertex(v1);
	s_Data.VertexBuffer->AddVertex(v2);
	s_Data.VertexBuffer->AddVertex(v3);
	s_Data.VertexBuffer->AddVertex(v4);

}
void SpriteBatch::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& source_pos, const glm::vec2& source_size, Ref<Texture2D> texture, float rotation, const glm::vec2& origin_offset)
{
	if (!s_Data.VertexBuffer->HasCapacity() || BatchTextureManager::IsOccupied()) {
		EndBatch();
		BeginBatch(s_Data.ViewProjectionMatrix);
	}

	float result;
	if (!BatchTextureManager::CheckTexture(texture->GetRendererTexture(), &result)) {
		result = BatchTextureManager::AddTexture(texture->GetRendererTexture());
		texture->BindTextureUnit((int)result);
	}

	Color c = { 1.0f,1.0f,1.0f,1.0f };

	glm::vec4 v1_Pos = glm::vec4(0.0f + origin_offset.x, size.y + origin_offset.y, 1.0f, 1.0f);
	glm::vec4 v2_Pos = glm::vec4(0.0f + origin_offset.x, 0.0f + origin_offset.y, 1.0f, 1.0f);
	glm::vec4 v3_Pos = glm::vec4(size.x + origin_offset.x, 0.0f + origin_offset.y, 1.0f, 1.0f);
	glm::vec4 v4_Pos = glm::vec4(size.x + origin_offset.x, size.y, size.y + origin_offset.y, 1.0f);

	glm::mat4 rotation_transform = glm::mat4(1.0f);
	rotation_transform = glm::rotate(rotation_transform, rotation, glm::vec3(0.0f, 0.0f, 1.0f));

	v1_Pos = v1_Pos * rotation_transform;
	v2_Pos = v2_Pos * rotation_transform;
	v3_Pos = v3_Pos * rotation_transform;
	v4_Pos = v4_Pos * rotation_transform;

	v1_Pos += glm::vec4(pos.x, pos.y, 0.0f, 0.0f);
	v2_Pos += glm::vec4(pos.x, pos.y, 0.0f, 0.0f);
	v3_Pos += glm::vec4(pos.x, pos.y, 0.0f, 0.0f);
	v4_Pos += glm::vec4(pos.x, pos.y, 0.0f, 0.0f);

	int t_width = texture->GetWidth();
	int t_height = texture->GetHeight();

	float tx, ty, tw, th;

	tx = source_pos.x / t_width;
	ty = 1 - (source_pos.y / t_height);

	tw = source_size.x / t_width;
	th = source_size.y / t_height;

	glm::vec2 tc1 = glm::vec2(tx, ty + th);
	glm::vec2 tc2 = glm::vec2(tx, ty);
	glm::vec2 tc3 = glm::vec2(tx + tw, ty);
	glm::vec2 tc4 = glm::vec2(tx + tw, ty + th);

	Vertex v1 = { v1_Pos.x, v1_Pos.y, 0.0f, c, tc1.x, tc1.y, result,1.0f};
	Vertex v2 = { v2_Pos.x, v2_Pos.y, 0.0f, c, tc2.x, tc2.y, result,1.0f};
	Vertex v3 = { v3_Pos.x, v3_Pos.y, 0.0f, c, tc3.x, tc3.y, result,1.0f};
	Vertex v4 = { v4_Pos.x, v4_Pos.y, 0.0f, c, tc4.x, tc4.y, result,1.0f};

	s_Data.VertexBuffer->AddVertex(v1);
	s_Data.VertexBuffer->AddVertex(v2);
	s_Data.VertexBuffer->AddVertex(v3);
	s_Data.VertexBuffer->AddVertex(v4);
}

void SpriteBatch::DrawQuad(const glm::mat4& transform, const Color& c)
{

	if (!s_Data.VertexBuffer->HasCapacity()) {
		EndBatch();
		BeginBatch(s_Data.ViewProjectionMatrix);
	}

	glm::vec4 pos1 = transform * glm::vec4{-0.5f, -0.5f, 1.0f, 1.0f };
	glm::vec4 pos2 = transform * glm::vec4{-0.5f,  0.5f, 1.0f, 1.0f };
	glm::vec4 pos3 = transform * glm::vec4{ 0.5f,  0.5f, 1.0f, 1.0f };
	glm::vec4 pos4 = transform * glm::vec4{ 0.5f, -0.5f, 1.0f, 1.0f };

	Vertex v1 = { pos1.x, pos1.y, pos1.z, c, 0.0f, 0.0f, 0.0f, 1.0f};
	Vertex v2 = { pos2.x, pos2.y, pos2.z, c, 0.0f, 0.0f, 0.0f, 1.0f};
	Vertex v3 = { pos3.x, pos3.y, pos3.z, c, 0.0f, 0.0f, 0.0f, 1.0f};
	Vertex v4 = { pos4.x, pos4.y, pos4.z, c, 0.0f, 0.0f, 0.0f, 1.0f};

	s_Data.VertexBuffer->AddVertex(v1);
	s_Data.VertexBuffer->AddVertex(v2);
	s_Data.VertexBuffer->AddVertex(v3);
	s_Data.VertexBuffer->AddVertex(v4);
}
void SpriteBatch::DrawQuad(const glm::mat4& transform, const Color& c,Ref<Texture2D> texture, float tiling_factor)
{

	if (!s_Data.VertexBuffer->HasCapacity() || BatchTextureManager::IsOccupied()) {
		EndBatch();
		BeginBatch(s_Data.ViewProjectionMatrix);
	}

	float result;
	if (!BatchTextureManager::CheckTexture(texture->GetRendererTexture(), &result)) {
		result = BatchTextureManager::AddTexture(texture->GetRendererTexture());
		texture->BindTextureUnit((int)result);
	}

	glm::vec4 pos1 = transform * glm::vec4{ -0.5f, -0.5f, 1.0f, 1.0f };
	glm::vec4 pos2 = transform * glm::vec4{ -0.5f,  0.5f, 1.0f, 1.0f };
	glm::vec4 pos3 = transform * glm::vec4{  0.5f,  0.5f, 1.0f, 1.0f  };
	glm::vec4 pos4 = transform * glm::vec4{  0.5f, -0.5f, 1.0f, 1.0f };

	Vertex v1 = { pos1.x, pos1.y, pos1.z, c, 0.0f, 0.0f, result, tiling_factor};
	Vertex v2 = { pos2.x, pos2.y, pos2.z, c, 0.0f, 1.0f, result, tiling_factor};
	Vertex v3 = { pos3.x, pos3.y, pos3.z, c, 1.0f, 1.0f, result, tiling_factor};
	Vertex v4 = { pos4.x, pos4.y, pos4.z, c, 1.0f, 0.0f, result, tiling_factor};

	s_Data.VertexBuffer->AddVertex(v1);
	s_Data.VertexBuffer->AddVertex(v2);
	s_Data.VertexBuffer->AddVertex(v3);
	s_Data.VertexBuffer->AddVertex(v4);

}
void SpriteBatch::DrawQuad(const glm::mat4& transform, const Color& c,const glm::vec2& source_pos, const glm::vec2& source_size, Ref<Texture2D> texture)
{

	if (!s_Data.VertexBuffer->HasCapacity() || BatchTextureManager::IsOccupied()) {
		EndBatch();
		BeginBatch(s_Data.ViewProjectionMatrix);
	}

	float result;
	if (!BatchTextureManager::CheckTexture(texture->GetRendererTexture(), &result)) {
		result = BatchTextureManager::AddTexture(texture->GetRendererTexture());
		texture->BindTextureUnit((int)result);
	}

	int t_width = texture->GetWidth();
	int t_height = texture->GetHeight();

	float tx, ty, tw, th;

	tx = source_pos.x / t_width;
	ty = 1 - (source_pos.y / t_height);

	tw = source_size.x / t_width;
	th = source_size.y / t_height;

	glm::vec2 tc1 = glm::vec2(tx, ty + th);
	glm::vec2 tc2 = glm::vec2(tx, ty);
	glm::vec2 tc3 = glm::vec2(tx + tw, ty);
	glm::vec2 tc4 = glm::vec2(tx + tw, ty + th);

	glm::vec4 pos1 = transform * glm::vec4{ -0.5f, -0.5f, 1.0f, 1.0f };
	glm::vec4 pos2 = transform * glm::vec4{ -0.5f,  0.5f, 1.0f, 1.0f };
	glm::vec4 pos3 = transform * glm::vec4{ 0.5f,  0.5f, 1.0f, 1.0f };
	glm::vec4 pos4 = transform * glm::vec4{ 0.5f, -0.5f, 1.0f, 1.0f };

	Vertex v1 = { pos1.x, pos1.y, pos1.z, c, tc1.x, tc1.y, result, 1.0f};
	Vertex v2 = { pos2.x, pos2.y, pos2.z, c, tc2.x, tc2.y, result, 1.0f};
	Vertex v3 = { pos3.x, pos3.y, pos3.z, c, tc3.x, tc3.y, result, 1.0f};
	Vertex v4 = { pos4.x, pos4.y, pos4.z, c, tc4.x, tc4.y, result, 1.0f};

	s_Data.VertexBuffer->AddVertex(v1);
	s_Data.VertexBuffer->AddVertex(v2);
	s_Data.VertexBuffer->AddVertex(v3);
	s_Data.VertexBuffer->AddVertex(v4);

}

void SpriteBatch::SetShader(Ref<Shader> shader)
{
	s_Data.Shader = shader;
}

void SpriteBatch::EndBatch()
{
	if (s_Data.VertexBuffer->GetNextVertex() == s_Data.VertexBuffer->GetVertices()) return;

	s_Data.Texture_0->BindTextureUnit(0);
	s_Data.Shader->Bind();
	s_Data.Shader->SetUniformMatrix4x4(1, &s_Data.ViewProjectionMatrix[0][0], "u_ProjectionMatrix");
	s_Data.Shader->SetUniform1ia(s_Data.TextureSlots, s_Data.Samplers, "u_Samplers");
	RenderingPipeline::GetData().Renderer->DrawVertexBuffer(s_Data.VertexBuffer);
	s_Data.Shader->UnBind();
}

const SpriteBatchData& SpriteBatch::GetData()
{
	return s_Data;
}







