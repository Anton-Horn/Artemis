
#include "RenderingPipeline.h"
#include "SpriteBatch.h"

#include "Rendering/OpenGL/OpenGLRenderer.h"




RenderingPipelineData RenderingPipeline::s_Data;

void RenderingPipeline::Init()
{

#ifdef ART_WINDOWS
		s_Data.API = RenderingAPI::OpenGL;
#endif

	if (s_Data.API == RenderingAPI::OpenGL) {
		s_Data.Renderer = CreatePtr<Renderer>();

		s_Data.Renderer->SetMaxQuads(SpriteBatch::GetData().MaxQuads); 
		s_Data.Renderer->BeginInit();

		SpriteBatch::Init();

		s_Data.Renderer->EndInit();


	}
}

void RenderingPipeline::BeginFrame()
{
	SpriteBatch::BeginFrame();
}


