#pragma once

#include "Renderer.h"

#include "Core/Core.h"
#include "glm/glm.hpp"
#include "Vertex.h"

class Texture2D;
class Shader;

struct SpriteBatchData
{

	 Ref<VertexBuffer> VertexBuffer;
     Ref<Shader> Shader;
	 Ref<Texture2D> Texture_0;

	 glm::mat4 ViewProjectionMatrix;

	 int TextureSlots;
	 const int MaxQuads = 10000;

	 int BatchCount;

	 int* Samplers;
};

struct SpriteRenderComponent;
struct TransformComponent;

class SpriteBatch
{

private:

	static SpriteBatchData s_Data;

public:

	static void Init();
	static void Shutdown();

	static void BeginFrame();

	static void BeginBatch(const glm::mat4& ViewProjectionMatrix);

	static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Color& c);
	static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Color& c, float rotation, const glm::vec2& origin_offset);
	static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, Ref<Texture2D> texture, float tiling_factor);
	static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, Ref<Texture2D> texture, float tiling_factor, float rotation, const glm::vec2& origin_offset);
	static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& source_pos, const glm::vec2& source_size, Ref<Texture2D> texture);
	static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& source_pos, const glm::vec2& source_size, Ref<Texture2D> texture, float rotation, const glm::vec2& origin_offset);

	static void DrawQuad(const glm::mat4& transform, const Color& c);
	static void DrawQuad(const glm::mat4& transform, const Color& c, Ref<Texture2D> texture, float tiling_factor);
	static void DrawQuad(const glm::mat4& transform, const Color& c, const glm::vec2& source_pos, const glm::vec2& source_size, Ref<Texture2D> texture);

	static void SetShader(Ref<Shader> shader);

	static void EndBatch();
	
	static const SpriteBatchData& GetData();

};



