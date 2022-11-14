#pragma once

#include "Renderer.h"

enum class RenderingAPI {
	None,
	OpenGL,
	Direct11,
	Vulkan
};

struct RenderingPipelineData {

	RenderingAPI API = RenderingAPI::None;
	Ptr<Renderer> Renderer;

	RenderingPipelineData(RenderingPipelineData&) = delete;
	RenderingPipelineData() = default;

};

class RenderingPipeline{

private:

	static RenderingPipelineData s_Data;


public:

	static void Init();

	static const RenderingPipelineData& GetData() {
			return s_Data;
		}

	static void BeginFrame();

};


